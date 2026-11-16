/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marisous <marisous@student.42lisb...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 09:43:47 by marisous          #+#    #+#             */
/*   Updated: 2026/11/16 12:50:40 by marisous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUSKO_H
# define GET_NEXT_LINE_BONUSKO_H

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
	struct s_gnl	*next;
}			t_gnl;

t_gnl			*ft_get_gnl(t_gnl **gnl, int fd);
void			ft_del_gnl(t_gnl **gnl, int fd);
unsigned char	*ft_memjoin(unsigned char *s1, unsigned char *s2,
					ssize_t ss1, ssize_t ss2);
unsigned char	*ft_split2(t_gnl *elem, const unsigned char c);
char			*get_next_line(int fd);
t_gnl			new_gnl(t_gnl single, int fd);
#endif
