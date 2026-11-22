/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marisous <marisous@student.42lisb...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 10:16:55 by marisous          #+#    #+#             */
/*   Updated: 2026/11/22 17:54:14 by marisous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	new_gnl(t_gnl *elem, int fd, int opt)
{
	if (opt == 1)
	{
		if (elem->retval != NULL)
			free(elem->retval);
	}
	elem->retval = NULL;
	elem->retsize = 0;
	elem->read0_1st = 0;
	if (elem->fd != -1)
		return ;
	elem->fd = fd;
	elem->leftover = 0;
	elem->buff0 = 0;
	elem->bytes_read = 0;
}

unsigned char	*ft_split2(t_gnl *elem, const unsigned char c)
{
	ssize_t			index;
	unsigned char	*s;

	elem->leftover = elem->bytes_read;
	index = elem->buff0;
	s = elem->buffer + elem->buff0;
	while (index < elem->bytes_read)
	{
		index++;
		if (*s == c || index == elem->bytes_read)
			break ;
		s++;
	}
	elem->retval = ft_memjoin(elem->retval, elem->buffer + elem->buff0,
			elem->retsize, index - elem->buff0);
	if (elem->retval == NULL)
		return (NULL);
	elem->leftover -= index;
	elem->retsize += index - elem->buff0;
	if (index == elem->bytes_read)
		index = 0;
	elem->buff0 = index;
	return (elem->retval);
}

unsigned char	*ft_memjoin(unsigned char *s1, unsigned char *s2,
					ssize_t ss1, ssize_t ss2)
{
	unsigned char	*retval;
	ssize_t			iter;

	iter = 0;
	retval = malloc((ss1 + ss2) * sizeof(unsigned char));
	if (retval == NULL || s2 == NULL)
	{
		free(s1);
		return (NULL);
	}
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

int	preliminary_and_split2(t_gnl *elem)
{
	if (elem->leftover == 0)
	{
		elem->bytes_read = read(elem->fd, elem->buffer, BUFFER_SIZE);
		if (elem->bytes_read < 0)
		{
			new_gnl(elem, elem->fd, 1);
			return (1);
		}
	}
	if (elem->bytes_read == 0)
	{
		if (!elem->read0_1st && elem->retval != NULL)
			elem->read0_1st = 1;
		else if (elem->retval == NULL)
			return (1);
	}
	if (elem->bytes_read != 0)
		elem->retval = ft_split2(elem, '\n');
	if (elem->retval == NULL)
		return (1);
	return (0);
}
