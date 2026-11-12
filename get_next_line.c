/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marisous <marisous@student.42lisb...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 09:44:07 by marisous          #+#    #+#             */
/*   Updated: 2026/11/12 20:56:21 by marisous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stddef.h>

/* char *get_next_line(int fd); */
/* ssize_t read(int fd, void *buf, size_t nbyte); */

t_gnl *ft_get_gnl(t_gnl **gnl, int fd);
void ft_del_gnl(t_gnl **gnl, int fd);

t_gnl *ft_get_gnl(t_gnl **gnl, int fd)
{
	t_gnl *this;
	t_gnl *prev;

	this = *gnl;
	while (this != NULL)
	{
		if (this->fd == fd)
			return (this);
		prev = this;
		this = this->next;
	}
	this = malloc(sizeof(t_gnl));
	if (this == NULL)
		return (NULL);
	this->fd = fd;
	this->next = NULL;
	this->retval = NULL;
	this->ret_size = 0;
	this->bytes_read = 0;
	if (*gnl == NULL)
		*gnl = this;
	else
		prev->next = this;
	return (this);
}

void ft_del_gnl(t_gnl **gnl, int fd)
{
	t_gnl *this;
	t_gnl *tmp;

	this = *gnl;
	if (this == NULL)
		return;
	if (this->fd == fd)
	{
		*gnl = (*gnl)->next;
		free(this);
		return ;
	}
	while (this->next != NULL)
	{
		if (this->next->fd != fd)
		{
			this = this->next;
			continue ;
		}
		tmp = this->next;
		this->next = this->next->next;
		free(tmp);
		return ;
	}
}


char	*get_next_line(int fd)
{
	static t_gnl	*gnl_lst = NULL;
	t_gnl			*this;
	char			*aux[2];
	ssize_t			bytes_read;
	size_t			line_len;
	
	this = ft_get_gnl(&gnl_lst, fd);
	aux[0] = ft_strjoin("", "");
	aux[1] = NULL;
	while (1)
	{
		if (aux[1] == NULL && (bytes_read = read(fd, this->buffer, BUFFER_SIZE)) < 0)
			break ;
		aux[1] = ft_strchr(this->buffer, '\n');
		this->buffer[bytes_read] = '\0';
		this->buffer[bytes_read+1] = '\0';
		if (aux[1] != NULL)
		{
			line_len = aux[1] - this->buffer + 1;
			ft_memmove(aux[1] + 2, aux[1] + 1, bytes_read - line_len);
			*(aux[1] + 1) = '\0';
		}
		this->retval = ft_strjoin(aux[0], this->buffer);
		free(aux[0]);
		aux[0] = this->retval;
		if (aux[1] != NULL || !bytes_read)
		{
			this->retval = NULL;
			bytes_read = ft_strlcpy(this->buffer, aux[1], line_len);
			return (aux[0]);
		}
	}
	ft_del_gnl(&gnl_lst, fd);
	return (NULL);
}

size_t	ft_size_retval(void const *buffer, void const *chr)
{
	size_t retval;

	retval = 0;
	while (buffer < chr)
	{
		buffer++;
		retval++;
	}
	return (retval);
}

char	*get_next_line2(int fd)
{
	static t_gnl	*gnl_lst = NULL;
	t_gnl			*this;
	char			*aux[2];
	ssize_t			bytes_read;
	size_t			tmp;
	this = ft_get_gnl(&gnl_lst, fd);
	if (this == NULL)
		return (NULL);
	/* string[0] = ft_strjoin("", ""); */
	/* string[1] = NULL; */
	while (1)
	{
		if (this->bytes_read == 0)
			this->bytes_read = read(fd, this->buffer, BUFFER_SIZE);
		if (this->bytes_read < 0) break ;
		aux[0] = ft_memchr(this->buffer, '\n', bytes_read);
		if (aux[0] != NULL)
		{
			tmp = ft_size_retval(this->buffer, aux[0]);
			this->retval = ft_memjoin(this->retval, this->buffer,
				this->ret_size, tmp);
			this->ret_size += tmp;
			this->retval = ft_memjoin(this->retval, "\n\0", this->ret_size, 2);
			free(aux[0]);
		}
		free(string[0]);
		string[0] = this->retval;
		if (string[1] != NULL || !bytes_read)
		{
			this->retval = NULL;
			return (string[0]);
		}
		bytes_read = ft_strlcpy(this->buffer, string[1], ft_strlen(string[1])) + 1;
	}
	ft_del_gnl(&gnl_lst, fd);
	return (NULL);
}

