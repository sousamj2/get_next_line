/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marisous <marisous@student.42lisb...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 09:44:07 by marisous          #+#    #+#             */
/*   Updated: 2026/11/10 11:22:46 by marisous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *get_next_line(int fd);
ssize_t read(int fd, void *buf, size_t nbyte);

char *get_next_line(int fd)
{
	static char buffer[BUFFER_SIZE];
	static size_t start = 0;
	ssize_t bytes_read;
	static char * string[4];
	string[0] = "";
	if (start == 0) 
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		string[2] = buffer;
		string[1] = "";
	}
	else if ((string[1] = ft_strchr(buffer + start, 10)) == NULL) // \n not found
		string[0] = ft_strjoin(string[0], string[1]);

	return(string[0]);
}
