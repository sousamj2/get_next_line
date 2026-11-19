/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marisous <marisous@student.42lisb...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 10:16:55 by marisous          #+#    #+#             */
/*   Updated: 2026/11/19 13:00:12 by marisous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <strings.h>

void	new_gnl_bonus(t_gnl *a_gnl, int fd, int opt)
{
	if (a_gnl[0].fd == -1)
		while (opt < FOPEN_MAX)
		{
			opt++;
			a_gnl[opt].init = 0;
		}
	if (opt == 1)
	{
		if (a_gnl[fd].retval != NULL)
			free(a_gnl[fd].retval);
		a_gnl[fd].init = 0;
		bzero(a_gnl[fd].buffer, BUFFER_SIZE);
		return ;
	}
	a_gnl[fd].retval = NULL;
	a_gnl[fd].retsize = 0;
	a_gnl[fd].read0_1st = 0;
	if (a_gnl[fd].init == 0)
		return ;
	a_gnl[fd].init = 1;
	a_gnl[fd].fd = fd;
	a_gnl[fd].leftover = 0;
	a_gnl[fd].buff0 = 0;
	a_gnl[fd].bytes_read = 0;
}

unsigned char	*ft_split2_bonus(t_gnl *a_gnl, const unsigned char c, int fd)
{
	ssize_t			index;
	unsigned char	*s;

	a_gnl[fd].leftover = a_gnl[fd].bytes_read;
	index = a_gnl[fd].buff0;
	s = a_gnl[fd].buffer + a_gnl[fd].buff0;
	while (index < a_gnl[fd].bytes_read)
	{
		index++;
		if (*s == c || index == a_gnl[fd].bytes_read)
			break ;
		s++;
	}
	a_gnl[fd].retval = ft_memjoin_bonus(a_gnl[fd].retval, a_gnl[fd].buffer
		+ a_gnl[fd].buff0, a_gnl[fd].retsize, index - a_gnl[fd].buff0);
	if (a_gnl[fd].retval == NULL)
		return (NULL);
	a_gnl[fd].leftover -= index;
	a_gnl[fd].retsize += index - a_gnl[fd].buff0;
	if (index == a_gnl[fd].bytes_read)
		index = 0;
	a_gnl[fd].buff0 = index;
	return (a_gnl[fd].retval);
}

unsigned char	*ft_memjoin_bonus(unsigned char *s1, unsigned char *s2,
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

int	preliminary_and_split2_bonus(t_gnl *a_gnl, int fd)
{
	if (a_gnl[fd].leftover == 0)
	{
		a_gnl[fd].bytes_read = read(a_gnl[fd].fd, a_gnl[fd].buffer, BUFFER_SIZE);
		if (a_gnl[fd].bytes_read < 0)
		{
			new_gnl_bonus(a_gnl, fd, 1);
			return (1);
		}
	}
	if (a_gnl[fd].bytes_read == 0)
	{
		if (!a_gnl[fd].read0_1st && a_gnl[fd].retval != NULL)
			a_gnl[fd].read0_1st = 1;
		else if (a_gnl[fd].retval == NULL)
			return (1);
	}
	if (a_gnl[fd].bytes_read != 0)
        a_gnl[fd].retval = ft_split2_bonus(a_gnl, '\n', fd);
	if (a_gnl[fd].retval == NULL)
		return (1);
	return (0);
}
