/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marisous <marisous@student.42lisb...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 09:43:47 by marisous          #+#    #+#             */
/*   Updated: 2026/11/12 01:44:53 by marisous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

/**
 * @brief Allocates and returns a new string, which is the result of the
 * concatenation of 's1' and 's2'.
 *
 * @param s1 Prefix string.
 * @param s2 Suffix string.
 * @return The new concatenated string, or NULL if memory allocation fails.
 */
char			*ft_strjoin(char const *s1, char const *s2);

/**
 * @brief Calculates the length of the string s.
 *
 * @param s Null-terminated string to measure.
 * @return The number of characters preceding the terminating null character.
 */
size_t			ft_strlen(const char *s);

/**
 * @brief Locates the first occurrence of character c in the string s.
 *
 * @param s String to search.
 * @param c Character to locate (converted to char).
 * @return Pointer to the matched character or NULL if not found.
 */
char			*ft_strchr(const char *s, int c);

char			*get_next_line(int fd);

typedef struct s_gnl
{
	int		fd;
	char	buffer[BUFFER_SIZE + 1];
	char	*retval;
	s_gnl	*next;
}			t_gnl;

#endif
