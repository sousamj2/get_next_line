/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marisous <marisous@student.42lisb...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 09:44:07 by marisous          #+#    #+#             */
/*   Updated: 2026/11/16 06:13:50 by marisous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stddef.h>
#include <stdio.h>

char	*get_next_line(int fd)
{
	/* static t_gnl	*gnl_lst = NULL; */
	t_gnl			*elem;
	unsigned char	*retval;
	ssize_t			bytes_read;
	static t_gnl	single = {.fd = -1};
	int bufsize		= BUFFER_SIZE;

	/* elem = ft_get_gnl(&gnl_lst, fd); */
	single = new_gnl(single, fd);
	elem = &single;
	while (1)
	{
		if (elem->leftover == 0)
		{
			bytes_read = read(fd, elem->buffer, bufsize);
			if (bytes_read < 0)
				break ;
		}
		/* if (bytes_read == 0) */
		/* 	ft_del_gnl(&gnl_lst, fd); */
		if (bytes_read == 0)
			elem->read0_1st = 1;
		
		elem->retval = ft_split2(elem, '\n');
		if (elem->leftover != 0 || elem->read0_1st)//&& (elem->retval != NULL))
		{
			elem->read0_1st = 0;			
			if (!BINNARY_FILE)
				retval = ft_memjoin(elem->retval, (unsigned char *)"",
						elem->retsize, 1);
			elem->retval = NULL;
			return ((char *) retval);
		}
		if (bytes_read == 0)
			break;
	}
	return (NULL);
}
