/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marisous <marisous@student.42lisb...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 09:43:47 by marisous          #+#    #+#             */
/*   Updated: 2026/11/22 17:59:43 by marisous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>
/* #define MAXMEMORY 999916 */

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# elif BUFFER_SIZE > 500000 
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 500000
# elif BUFFER_SIZE <= 0
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# ifndef FOPEN_MAX_MJ
#  define FOPEN_MAX_MJ 1001
# endif

# ifndef BINNARY_FILE
#  define BINNARY_FILE 0
# endif

/**
 * @brief Holds all persistent and per-call state for one fd in multi-fd GNL.
 *
 * @var s_gnl::fd
 *   File descriptor this slot is bound to.
 * @var s_gnl::buffer
 *   Raw read buffer of BUFFER_SIZE bytes filled by each read(2) call.
 * @var s_gnl::retval
 *   Heap-allocated accumulator for the line being built across reads.
 * @var s_gnl::retsize
 *   Number of bytes currently stored in retval (excluding any terminator).
 * @var s_gnl::memsize
 *   Actual allocated capacity of retval (may be larger than retsize to
 *   reduce reallocations via the doubling strategy in ft_new_malloc).
 * @var s_gnl::leftover
 *   Bytes still unprocessed in buffer from the previous read.
 * @var s_gnl::buff0
 *   Index into buffer where the unprocessed data starts.
 * @var s_gnl::nb_read
 *   Return value of the last read(2) call (0 on EOF, <0 on error).
 * @var s_gnl::init
 *   Flag set to 1 once the slot has been fully initialised for its fd,
 *   preventing redundant re-initialisation on subsequent calls.
 * @var s_gnl::read0
 *   Flag set to 1 on the first EOF encountered while retval is non-NULL,
 *   allowing the last line (without trailing newline) to be returned.
 */
typedef struct s_gnl
{
	int				fd;
	unsigned char	buffer[BUFFER_SIZE];
	unsigned char	*retval;
	ssize_t			retsize;
	ssize_t			memsize;
	ssize_t			leftover;
	ssize_t			buff0;
	ssize_t			nb_read;
	int				init;
	int				read0;
}			t_gnl;

/**
 * @brief Scans the buffer for delimiter c and appends the segment to retval.
 *
 * Advances through a_gnl[fd].buffer from buff0, stopping at c or at the end
 * of the bytes read. Appends the scanned segment to a_gnl[fd].retval via
 * ft_memjoin_bonus, then updates buff0, retsize, and leftover accordingly.
 *
 * @param a_gnl Array of t_gnl structures, one per file descriptor.
 * @param c     Delimiter byte to search for (typically '\\n').
 * @param fd    Index into a_gnl identifying the active file descriptor.
 * @return Updated a_gnl[fd].retval, or NULL on allocation failure.
 */
unsigned char	*ft_split2_bonus(t_gnl *a_gnl, const unsigned char c, int fd);

/**
 * @brief Reads the next line from a file descriptor (multi-fd version).
 *
 * Supports up to FOPEN_MAX_MJ simultaneously open file descriptors by
 * indexing into a static array of t_gnl slots. Returns one line at a time
 * including its trailing newline when present. When BINNARY_FILE is 0
 * (default) a null terminator is appended. Returns NULL on EOF, error, or
 * when fd is out of range.
 *
 * @param fd File descriptor to read from (must be in [0, FOPEN_MAX_MJ)).
 * @return Heap-allocated string containing the next line, or NULL on
 *         EOF / error. The caller is responsible for freeing it.
 */
char			*get_next_line(int fd);

/**
 * @brief Performs a read (if needed) then delegates to ft_split2_bonus.
 *
 * If no leftover bytes remain a new read(2) is issued. On read error the
 * slot is fully reset and 1 is returned. On EOF with a pending retval the
 * read0 flag is set so the caller can still return that last partial line.
 *
 * @param a_gnl Array of t_gnl structures indexed by fd.
 * @param fd    File descriptor whose slot should be advanced.
 * @return 1 if the caller should stop looping (EOF, error, or NULL retval),
 *         0 to continue accumulating data.
 */
int				preliminary_and_split2_bonus(t_gnl *a_gnl, int fd);

/**
 * @brief Initialises or resets a t_gnl slot for a new line read.
 *
 * When opt == 1 the existing retval is freed and all fields of a_gnl[fd]
 * are reset (error recovery path). When opt == 0 only the per-call fields
 * (retval, retsize, memsize, read0) are cleared; the fd-level fields
 * (init, fd, leftover, buff0, nb_read) are only set when init == 0
 * (first use of the slot).
 *
 * @param a_gnl Array of t_gnl structures indexed by fd.
 * @param fd    File descriptor whose slot to initialise or reset.
 * @param opt   0 for a normal per-line reset, 1 for a full error reset.
 */
void			new_gnl_bonus(t_gnl *a_gnl, int fd, int opt);

/**
 * @brief Smart realloc that grows retval with an optional doubling strategy.
 *
 * Returns the existing retval buffer without allocating when the current
 * memsize is large enough to hold retsize + ss2 more bytes (non-last call).
 * Otherwise allocates a new buffer: on the final call (last != 0) the exact
 * size is used; for mid-line chunks smaller than BUFFER_SIZE the exact size
 * is used too; for larger chunks the capacity is doubled to amortise
 * reallocations. Sets *iter to elem->retsize so the caller can resume
 * copying at the right offset.
 *
 * @param elem Pointer to the active t_gnl state structure.
 * @param iter Output parameter set to elem->retsize when reusing the buffer,
 *             or left at 0 when a new allocation is made.
 * @param ss2  Number of additional bytes that need to fit in the buffer.
 * @param last Non-zero when this is the final join (adds null terminator
 *             space and forces an exact-size allocation).
 * @return Pointer to a buffer of at least (retsize + ss2) bytes, or NULL
 *         on allocation failure.
 */
unsigned char	*ft_new_malloc(t_gnl *elem, ssize_t *iter,
					ssize_t ss2, int last);

/**
 * @brief Concatenates s2 onto elem->retval using the smart allocator.
 *
 * Calls ft_new_malloc to obtain (or reuse) a buffer large enough for
 * elem->retsize + ss2 bytes, copies the existing retval content into it,
 * frees the old retval if a new allocation was made, then appends ss2
 * bytes from s2. If allocation fails or s2 is NULL, retval is freed and
 * NULL is returned.
 *
 * @param s2   Byte array to append (the new chunk from the buffer, or ""
 *             for the final null-terminator join).
 * @param ss1  Current number of bytes in elem->retval (== elem->retsize).
 * @param ss2  Number of bytes to copy from s2.
 * @param elem Pointer to the active t_gnl state structure whose retval is
 *             updated in place.
 * @return Pointer to the updated (and possibly reallocated) buffer, or NULL
 *         on failure.
 */
unsigned char	*ft_memjoin_bonus(unsigned char *s2,
					ssize_t ss1, ssize_t ss2, t_gnl *elem);

#endif
