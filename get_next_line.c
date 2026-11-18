/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marisous <marisous@student.42lisb...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 09:44:07 by marisous          #+#    #+#             */
/*   Updated: 2026/11/18 18:47:07 by marisous         ###   ########.fr       */
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
		if (preliminary_and_split2 (elem))
			break ;
		if (elem->leftover != 0
			|| elem->read0_1st || elem->retval[elem->retsize - 1] == '\n')
		{
			if (!BINNARY_FILE)
				retval = ft_memjoin(elem->retval, (unsigned char *)"",
						elem->retsize, 1);
			else
				retval = elem->retval;
			if (retval == NULL)
				return (NULL);
			elem->retval = NULL;
			return ((char *) retval);
		}
	}
	return (NULL);
}
