/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marisous <marisous@student.42lisb...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 09:43:47 by marisous          #+#    #+#             */
/*   Updated: 2026/11/13 18:23:55 by marisous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlen(const char *s);




char			*ft_strchr(const char *s, int c);
void			*ft_memchr(const void *s, int c, size_t n);

size_t			ft_strlcpy(char *dst, const char *src, size_t size);
void	*ft_memcpy(void *dest, const void *src, size_t n);

char	*ft_memmove(char *dest, const char *src, size_t n);



typedef struct s_gnl
{
	int		fd;
	char	buffer[BUFFER_SIZE+2];
	char	*retval;
	struct s_gnl	*next;
}			t_gnl;


#endif
/* unsigned char	*ft_memjoin(unsigned char *s1, unsigned char *s2, size_t ss1, size_t ss2); */
t_gnl *ft_get_gnl(t_gnl **gnl, int fd);
void ft_del_gnl(t_gnl **gnl, int fd);
size_t	ft_size_retval(void const *buffer, void const *chr);
char	*get_next_line(int fd);
