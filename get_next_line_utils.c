/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marisous <marisous@student.42lisb...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 10:16:55 by marisous          #+#    #+#             */
/*   Updated: 2026/11/16 09:54:06 by marisous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

/* t_gnl *ft_get_gnl(t_gnl **gnl, int fd); */
/* void ft_del_gnl(t_gnl **gnl, int fd); */
/* unsigned char *ft_split2(const unsigned char *s, const unsigned char c, */
/* 						 unsigned char **submem2, */
/* 						 size_t *sizestr2); */
/* unsigned char *ft_memjoin(unsigned char *s1, unsigned char *s2, */
/* 						  size_t ss1, size_t ss2, int opt); */

t_gnl	new_gnl(t_gnl single, int fd)
{
	single.retval = NULL;
	single.retsize = 0;
	if (single.fd != -1)
		return (single);
	single.fd = fd;
	single.next = NULL;
	single.leftover = 0;
	single.buff0 = 0;
	single.bytes_read = 0;
	single.read0_1st = 0;
	return (single);
}

t_gnl	*ft_get_gnl(t_gnl **gnl, int fd)
{
	t_gnl	*elem;
	t_gnl	*prev;

	elem = *gnl;
	while (elem != NULL)
	{
		if (elem->fd == fd)
			return (elem);
		prev = elem;
		elem = elem->next;
	}
	elem = malloc(sizeof(t_gnl));
	if (elem == NULL)
		return (NULL);
	elem->fd = fd;
	elem->next = NULL;
	elem->retval = NULL;
	elem->leftover = 0;
	elem->buff0 = 0;
	elem->retsize = 0;
	if (*gnl == NULL)
		*gnl = elem;
	else
		prev->next = elem;
	return (elem);
}

void	ft_del_gnl(t_gnl **gnl, int fd)
{
	t_gnl	*elem;
	t_gnl	*tmp;

	elem = *gnl;
	if (elem == NULL)
		return ;
	if (elem->fd == fd)
	{
		*gnl = (*gnl)->next;
		free(elem);
		return ;
	}
	while (elem->next != NULL)
	{
		if (elem->next->fd != fd)
		{
			elem = elem->next;
			continue ;
		}
		tmp = elem->next;
		elem->next = elem->next->next;
		free(tmp);
		return ;
	}
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
