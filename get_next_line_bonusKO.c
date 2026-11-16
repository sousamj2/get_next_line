/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marisous <marisous@student.42lisb...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 09:44:07 by marisous          #+#    #+#             */
/*   Updated: 2026/11/16 12:44:15 by marisous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stddef.h>
#include <stdio.h>

char	*get_next_line(int fd)
{
	t_gnl			*elem;
	unsigned char	*retval;
	static t_gnl	*gnl_lst = NULL;

	elem = ft_get_gnl(&gnl_lst, fd);
	while (1)
	{
		if (elem->leftover == 0)
		{
			elem->bytes_read = read(fd, elem->buffer, BUFFER_SIZE);
			if (elem->bytes_read < 0)
				break ;
		}
		if (elem->bytes_read == 0)
		{
			ft_del_gnl(&gnl_lst, fd);
			if (!elem->read0_1st && elem->retval != NULL)
				elem->read0_1st = 1;
			else
				break ;
		}
		if (elem->bytes_read != 0)
			elem->retval = ft_split2(elem, '\n');
		if (elem->leftover != 0 || elem->read0_1st)
		{
			if (!BINNARY_FILE)
				retval = ft_memjoin(elem->retval, (unsigned char *)"",
						elem->retsize, 1);
			if (retval == NULL)
				return (NULL);
			elem->retval = NULL;
			return ((char *) retval);
		}
	}
	return (NULL);
}
