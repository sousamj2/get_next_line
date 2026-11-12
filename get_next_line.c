/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marisous <marisous@student.42lisb...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 09:44:07 by marisous          #+#    #+#             */
/*   Updated: 2026/11/12 01:44:22 by marisous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* char *get_next_line(int fd); */
/* ssize_t read(int fd, void *buf, size_t nbyte); */

THEY ARE BOTH INCORRECT!
t_gnl *ft_get_gnl(t_gnl **gnl, int fd);
void ft_del_gnl(t_gnl **gnl, int fd);

t_gnl *ft_get_gnl(t_gnl **gnl, int fd)
{
 	t_gnl *this;
	
	while (gnl != NULL && *gnl != NULL && (*gnl)->next != NULL)
	{
		if ((*gnl)->fd == fd)
			return (*gnl);
		*gnl = (*gnl)->next;
	}
	this = malloc(sizeof(t_gnl));
	if (gnl == NULL)
		return (NULL);
	this->fd = fd;
	this->next = NULL;
	(*gnl)->next = this;
	return (this);
}

void ft_del_gnl(t_gnl **gnl, int fd)
{
 	t_gnl *this;
	
	if (gnl == NULL || *gnl == NULL)
		return;
	if (gnl[0]->fd == fd)
	{
		this = gnl[0];
		gnl[0] = gnl[0]->next;
		free(this);
	}
	while ((*gnl)->next != NULL && (*gnl)->next->fd != fd)
		(*gnl) = (*gnl)->next;
	this = gnl[0]->next;
	gnl[0] = gnl[0]->next->next;
	free(this);
}


char	*get_next_line(int fd)
{
	static t_gnl **gnl;
	t_gnl *this;
	this = ft_get_gnl(gnl, fd);


	
	
	string[0] = ft_strjoin("", "");
	while (1)
	{
		if (start == 0)
			bytes_read = read(fd, buffer, BUFFER_SIZE);
		string[1] = ft_strchr(buffer + start, 10);
		if (string[1] == NULL)
			buffer[bytes_read] = '\0';
		else
			*(++string[1]) = '\0';
		start = ft_strlen(buffer);
		string[2] = ft_strjoin(string[0], buffer);
		free(string[0]);
		if (string[2] == NULL)
			return (NULL);
		string[0] = string[2];
		if (string[1] != buffer + bytes_read + 1 )
		{
			buffer += bytes_read + 1;
			break ;
		}
		start = 0;
	}
	return (string[0]);
}

#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	int fd = open("text.txt", O_RDONLY);

	char *str;

	while ((str = get_next_line(fd)) != NULL)
	{
		printf("New line: %s", str);
		free(str);
	}
	
    return (0);
}
