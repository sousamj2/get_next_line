/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marisous <marisous@student.42lisb...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 09:44:07 by marisous          #+#    #+#             */
/*   Updated: 2026/11/22 17:49:59 by marisous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	unsigned char	*retval;
	static t_gnl	a_gnl[FOPEN_MAX_MJ];

	if (fd >= FOPEN_MAX_MJ || fd < 0)
		return (NULL);
	new_gnl_bonus(a_gnl, fd, 0);
	while (1)
	{
		if (preliminary_and_split2_bonus (a_gnl, fd))
			break ;
		if (a_gnl[fd].leftover != 0 || a_gnl[fd].read0 || (a_gnl[fd].retsize > 0
				&& a_gnl[fd].retval[a_gnl[fd].retsize - 1] == '\n'))
		{
			if (!BINNARY_FILE)
				retval = ft_memjoin_bonus((unsigned char *) "",
						a_gnl[fd].retsize, 1, &a_gnl[fd]);
			else
				retval = a_gnl[fd].retval;
			if (retval == NULL)
				return (NULL);
			a_gnl[fd].retval = NULL;
			return ((char *) retval);
		}
	}
	return (NULL);
}
