/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marisous <marisous@student.42lisb...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 09:43:47 by marisous          #+#    #+#             */
/*   Updated: 2026/11/18 17:38:32 by marisous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

/* # include <stdlib.h> */
# include <unistd.h>
# include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
/* #define MAXMEMORY 999916 */

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
}			t_gnl;

/* char			*ft_strjoin(char const *s1, char const *s2); */
/* size_t			ft_strlen(const char *s); */
/* char			*ft_strchr(const char *s, int c); */
/* void			*ft_memchr(const void *s, int c, size_t n); */
/* size_t			ft_strlcpy(char *dst, const char *src, size_t size); */
/* void	*ft_memcpy(void *dest, const void *src, size_t n); */
/* char	*ft_memmove(char *dest, const char *src, size_t n); */
/* unsigned char *ft_split2(const unsigned char *s, const unsigned char c, */
/* 						 unsigned char **submem2, */
/* 						 ssize_t *sizestr2); */

t_gnl			*ft_get_gnl(t_gnl **gnl, int fd);
void			ft_del_gnl(t_gnl **gnl, int fd);
unsigned char	*ft_memjoin(unsigned char *s1, unsigned char *s2,
					ssize_t ss1, ssize_t ss2);
unsigned char	*ft_split2(t_gnl *elem, const unsigned char c);
/*unsigned char *ft_split2(t_gnl *elem, const unsigned char c, ssize_t nread);*/
char			*get_next_line(int fd);
void			new_gnl(t_gnl *elem, int fd, int opt);
#endif
/* /\* unsigned char	*ft_memjoin(unsigned char
*s1, unsigned char *s2, size_t ss1, size_t ss2); *\/ */
/* t_gnl *ft_get_gnl(t_gnl **gnl, int fd); */
/* void ft_del_gnl(t_gnl **gnl, int fd); */
/* size_t	ft_size_retval(void const *buffer, void const *chr); */
/* char	*get_next_line(int fd); */
