/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marisous <marisous@student.42lisb...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 10:16:55 by marisous          #+#    #+#             */
/*   Updated: 2026/11/18 15:01:14 by marisous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_gnl	new_gnl(t_gnl elem, int fd)
{
	elem.retval = NULL;
	elem.retsize = 0;
	elem.read0_1st = 0;
	if (elem.fd != -1)
		return (elem);
	elem.fd = fd;
	elem.leftover = 0;
	elem.buff0 = 0;
	elem.bytes_read = 0;
	return (elem);
}


unsigned char	*ft_split2(t_gnl elem, const unsigned char c)
{
	ssize_t			index;
	unsigned char	*s;

	elem.leftover = elem.bytes_read;
	index = elem.buff0;
	s = elem.buffer + elem.buff0;
	while (index < elem.bytes_read)
	{
		index++;
		if (*s == c || index == elem.bytes_read)
			break ;
		s++;
	}
	elem.retval = ft_memjoin(elem.retval, elem.buffer + elem.buff0,
			elem.retsize, index - elem.buff0);
	if (elem.retval == NULL)
		return (NULL);
	elem.leftover -= index;
	elem.retsize += index - elem.buff0;
	if (index == elem.bytes_read)
		index = 0;
	elem.buff0 = index;
	return (elem.retval);
}

unsigned char	*ft_memjoin(unsigned char *s1, unsigned char *s2,
					ssize_t ss1, ssize_t ss2)
{
	unsigned char	*retval;
	ssize_t			iter;

	iter = 0;
	if (s2 == NULL)
		return (NULL);
	retval = malloc((ss1 + ss2) * sizeof(unsigned char));
	if (!retval)
		return (NULL);
	while (iter < ss1)
	{
		retval[iter] = s1[iter];
		iter++;
	}
	if (ss1)
		free(s1);
	while (iter < ss1 + ss2)
	{
		retval[iter] = s2[iter - ss1];
		iter++;
	}
	return (retval);
}
