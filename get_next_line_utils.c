/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marisous <marisous@student.42lisb...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 10:16:55 by marisous          #+#    #+#             */
/*   Updated: 2026/11/10 10:52:43 by marisous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*retval;
	size_t	size_alloc;

	if (!s1 || !s2)
		return (NULL);
	size_alloc = ft_strlen(s1) + ft_strlen(s2);
	retval = malloc((1 + size_alloc)* sizeof(char));
	if (!retval)
		return (NULL);
	while (*s1 != '\0')
	{
		*retval = *s1;
		retval++;
		s1++;
	}
	while (*s2 != '\0')
	{
		*retval = *s2;
		retval++;
		s2++;
	}
	*retval = '\0';
	return (retval - size_alloc);
}

char	*ft_strchr(const char *s, int c)
{
	char	*ichar;
	char	search;

	if (s == NULL)
		return (NULL);
	ichar = (char *) s;
	search = (char) c;
	if (search == '\0')
		return (ichar + ft_strlen(s));
	while (*ichar != '\0')
	{
		if (*ichar == search)
			return (ichar);
		ichar++;
	}
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s != '\0')
	{
		len++;
		s++;
	}
	return (len);
}
