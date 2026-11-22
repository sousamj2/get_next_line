/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marisous <marisous@student.42lisb...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 10:16:55 by marisous          #+#    #+#             */
/*   Updated: 2026/11/22 17:51:40 by marisous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	new_gnl_bonus(t_gnl *a_gnl, int fd, int opt)
{
	if (opt == 1)
	{
		if (a_gnl[fd].retval != NULL)
			free(a_gnl[fd].retval);
		a_gnl[fd].init = 0;
		a_gnl[fd].retval = NULL;
		a_gnl[fd].retsize = 0;
		a_gnl[fd].memsize = 0;
		a_gnl[fd].read0 = 0;
		return ;
	}
	a_gnl[fd].retval = NULL;
	a_gnl[fd].retsize = 0;
	a_gnl[fd].memsize = 0;
	a_gnl[fd].read0 = 0;
	if (a_gnl[fd].init == 1)
		return ;
	a_gnl[fd].init = 1;
	a_gnl[fd].fd = fd;
	a_gnl[fd].leftover = 0;
	a_gnl[fd].buff0 = 0;
	a_gnl[fd].nb_read = 0;
}

unsigned char	*ft_split2_bonus(t_gnl *a_gnl, const unsigned char c, int fd)
{
	ssize_t			index;
	unsigned char	*s;

	a_gnl[fd].leftover = a_gnl[fd].nb_read;
	index = a_gnl[fd].buff0;
	s = a_gnl[fd].buffer + a_gnl[fd].buff0;
	while (index < a_gnl[fd].nb_read)
	{
		index++;
		if (*s == c || index == a_gnl[fd].nb_read)
			break ;
		s++;
	}
	a_gnl[fd].retval = ft_memjoin_bonus(a_gnl[fd].buffer + a_gnl[fd].buff0,
			a_gnl[fd].retsize, index - a_gnl[fd].buff0, &a_gnl[fd]);
	if (a_gnl[fd].retval == NULL)
		return (NULL);
	a_gnl[fd].leftover -= index;
	a_gnl[fd].retsize += index - a_gnl[fd].buff0;
	if (index == a_gnl[fd].nb_read)
		index = 0;
	a_gnl[fd].buff0 = index;
	return (a_gnl[fd].retval);
}

int	preliminary_and_split2_bonus(t_gnl *a_gnl, int fd)
{
	if (a_gnl[fd].leftover == 0)
	{
		a_gnl[fd].nb_read = read(a_gnl[fd].fd, a_gnl[fd].buffer, BUFFER_SIZE);
		if (a_gnl[fd].nb_read < 0)
		{
			new_gnl_bonus(a_gnl, fd, 1);
			return (1);
		}
	}
	if (a_gnl[fd].nb_read == 0)
	{
		if (!a_gnl[fd].read0 && a_gnl[fd].retval != NULL)
			a_gnl[fd].read0 = 1;
		else if (a_gnl[fd].retval == NULL)
			return (1);
	}
	if (a_gnl[fd].nb_read != 0)
		a_gnl[fd].retval = ft_split2_bonus(a_gnl, '\n', fd);
	if (a_gnl[fd].retval == NULL)
		return (1);
	return (0);
}

unsigned char	*ft_memjoin_bonus(unsigned char *s2,
							ssize_t ss1, ssize_t ss2, t_gnl *elem)
{
	unsigned char	*retval;
	ssize_t			iter;

	iter = 0;
	retval = ft_new_malloc(elem, &iter, ss2, *s2 == '\0');
	if (retval == NULL || s2 == NULL)
	{
		free(elem->retval);
		return (NULL);
	}
	while (iter < ss1)
	{
		retval[iter] = elem->retval[iter];
		iter++;
	}
	if (retval != elem->retval)
		free(elem->retval);
	while (iter < ss1 + ss2)
	{
		retval[iter] = s2[iter - ss1];
		iter++;
	}
	return (retval);
}

unsigned char	*ft_new_malloc(t_gnl *elem, ssize_t *iter,
	ssize_t ss2, int last)
{
	unsigned char	*retval;

	if (elem->retsize + ss2 <= elem->memsize && !last)
	{
		*iter = elem->retsize;
		retval = elem->retval;
	}
	else
	{
		if (!elem->memsize)
			elem->memsize = ss2 + (last < 0);
		else if (ss2 < BUFFER_SIZE || BUFFER_SIZE == 1 || last)
			elem->memsize = elem->retsize + ss2;
		else
			elem->memsize = (elem->retsize + ss2) * 2;
		retval = malloc((elem->memsize) * sizeof(unsigned char));
		if (retval == NULL)
			return (NULL);
	}
	return (retval);
}
