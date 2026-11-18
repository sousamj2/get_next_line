/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marisous <marisous@student.42lisb...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 09:44:07 by marisous          #+#    #+#             */
/*   Updated: 2026/11/18 17:40:31 by marisous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	t_gnl			*elem;
	unsigned char	*retval;
	static t_gnl	single = {.fd = -1};

	elem = &single;
	new_gnl(elem, fd, 0);
	while (1)
	{
		if (elem->leftover == 0)
		{
			elem->bytes_read = read(fd, elem->buffer, BUFFER_SIZE);
			if (elem->bytes_read < 0)
			{
				new_gnl(elem, fd, 1);
				/* elem->retsize = 0; */
				/* elem->buff0 = 0; */
				/* elem->bytes_read = 0; */
				/* elem->read0_1st = 0; */
				/* elem->leftover = 0; */
				break ;
			}
		}
		if (elem->bytes_read == 0)
		{
			if (!elem->read0_1st && elem->retval != NULL)
				elem->read0_1st = 1;
			else if (elem->retval == NULL)
				break ;
		}
		if (elem->bytes_read != 0)
			elem->retval = ft_split2(elem, '\n');
		if (elem->retval == NULL)
			return (NULL);
		if (elem->leftover != 0
			|| elem->read0_1st || elem->retval[elem->retsize - 1] == '\n')
		{
			if (!BINNARY_FILE)
				retval = ft_memjoin(elem->retval, (unsigned char *)"",
						elem->retsize, 1);
			if (retval == NULL)
				return (NULL);
			elem->retval = NULL;
			return ((char *) retval);
		}
		if (elem->bytes_read == 0)
			break ;
	}
	return (NULL);
}
