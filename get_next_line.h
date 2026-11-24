/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marisous <marisous@student.42lisb...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 09:43:47 by marisous          #+#    #+#             */
/*   Updated: 2026/11/24 17:21:45 by marisous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# elif BUFFER_SIZE > 500000
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 500000
# elif BUFFER_SIZE <= 0
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# ifndef BINNARY_FILE
#  define BINNARY_FILE 0
# endif

/**
 * @brief Holds all persistent and per-call state for a single-fd GNL session.
 *
 * @var s_gnl::fd
 *   File descriptor being read. Initialised to -1 (unused).
 * @var s_gnl::buffer
 *   Raw read buffer of BUFFER_SIZE bytes filled by each read(2) call.
 * @var s_gnl::retval
 *   Heap-allocated accumulator for the line being built across reads.
 * @var s_gnl::retsize
 *   Number of bytes currently stored in retval (excluding any terminator).
 * @var s_gnl::leftover
 *   Bytes still unprocessed in buffer from the previous read.
 * @var s_gnl::buff0
 *   Index into buffer where the unprocessed data starts.
 * @var s_gnl::bytes_read
 *   Return value of the last read(2) call (0 on EOF, <0 on error).
 * @var s_gnl::read0_1st
 *   Flag set to 1 on the first EOF encountered while retval is non-NULL,
 *   allowing the last line (without trailing newline) to be returned.
 */
typedef struct s_gnl
{
	int				fd;
	unsigned char	buffer[BUFFER_SIZE];
	unsigned char	*retval;
	ssize_t			retsize;
	ssize_t			leftover;
	ssize_t			buff0;
	ssize_t			bytes_read;
	int				read0_1st;
}			t_gnl;

/**
 * @brief Concatenates two byte arrays into a newly allocated buffer.
 *
 * Allocates a buffer of (ss1 + ss2) bytes, copies ss1 bytes from s1 then
 * ss2 bytes from s2 into it, and frees s1 afterwards. If allocation fails
 * or s2 is NULL, s1 is freed and NULL is returned.
 *
 * @param s1  First byte array (may be NULL when ss1 == 0); freed on return.
 * @param s2  Second byte array to append.
 * @param ss1 Number of bytes to copy from s1.
 * @param ss2 Number of bytes to copy from s2.
 * @return Pointer to the newly allocated joined buffer, or NULL on failure.
 */
unsigned char	*ft_memjoin(unsigned char *s1, unsigned char *s2,
					ssize_t ss1, ssize_t ss2);

/**
 * @brief Scans the buffer for delimiter c and appends the segment to retval.
 *
 * Advances through elem->buffer from buff0, stopping at c or at the end of
 * the bytes already read. Appends the scanned segment to elem->retval via
 * ft_memjoin, then updates buff0, retsize, and leftover accordingly.
 *
 * @param elem Pointer to the active t_gnl state structure.
 * @param c    Delimiter byte to search for (typically '\\n').
 * @return Updated elem->retval, or NULL on allocation failure.
 */
unsigned char	*ft_split2(t_gnl *elem, const unsigned char c);

/**
 * @brief Reads the next line from a file descriptor.
 *
 * Returns one line at a time from fd, including the trailing newline when
 * present. Uses a static t_gnl to preserve state between calls. When
 * BINNARY_FILE is 0 (default) a null terminator is appended; otherwise the
 * raw byte sequence is returned. Returns NULL on EOF or error.
 *
 * @param fd File descriptor to read from.
 * @return Heap-allocated string containing the next line, or NULL on
 *         EOF / error. The caller is responsible for freeing it.
 */
char			*get_next_line(int fd);

/**
 * @brief Initialises or resets a t_gnl element for a new line read.
 *
 * When opt == 1 the existing retval is freed and all fields reset (error
 * recovery path). When opt == 0 only the per-call fields (retval, retsize,
 * read0_1st) are cleared; the fd-level fields (fd, leftover, buff0,
 * bytes_read) are only set if elem->fd is still -1 (first use).
 *
 * @param elem Pointer to the t_gnl structure to initialise or reset.
 * @param fd   File descriptor to associate with elem on first use.
 * @param opt  0 for a normal per-line reset, 1 for a full error reset.
 */
void			new_gnl(t_gnl *elem, int fd, int opt);

/**
 * @brief Performs a read (if needed) then delegates to ft_split2.
 *
 * If no leftover bytes remain a new read(2) is issued. On read error the
 * state is fully reset (opt 1) and 1 is returned. On EOF with a pending
 * retval the read0_1st flag is set so the caller can still return that last
 * partial line. Returns 1 to signal the caller to break out of its loop.
 *
 * @param elem Pointer to the active t_gnl state structure.
 * @return 1 if the caller should stop looping (EOF, error, or NULL retval),
 *         0 to continue accumulating data.
 */
int				preliminary_and_split2(t_gnl *elem);
#endif
