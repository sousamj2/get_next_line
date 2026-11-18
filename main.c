/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marisous <marisous@student.42lisb...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 09:45:00 by marisous          #+#    #+#             */
/*   Updated: 2026/11/18 17:56:04 by marisous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

static int		g_read_count = 0;
static int		g_n_max_read = -1;

ssize_t	__real_read(int fd, void *buf, size_t count);

ssize_t	__wrap_read(int fd, void *buf, size_t count)
{
	if (g_n_max_read != -1 && g_read_count + 1 > g_n_max_read)
		return (-1);
	g_read_count++;
	return (__real_read(fd, buf, count));
}

/* int main(void) */
/* { */
/* 	g_n_max_read = 2; */
/* 	char *filename = "read_error.txt";	 */
/* 	int fd = open(filename, O_RDONLY); */
/* 	char *str; */
/* 	int index; */
/* 	int max_val; */

/* 	index = 1; */
/* 	max_val = 15; */
/* 		str = get_next_line(fd); */
/* 		printf("%d: [%s]\n", index, str); */
/* 		free(str); */
/* 		index++; */
/* 		str = get_next_line(fd); */
/* 		printf("%d: [%s]\n", index, str); */
/* 		free(str); */
/* 		index++; */
/* 	/\* do { *\/ */
/* 	/\* 	str = get_next_line(fd); *\/ */
/* 	/\* 	/\\* printf("%d: [%s]\n", index, str); *\\/ *\/ */
/* 	/\* 	free(str); *\/ */
/* 	/\* 	/\\* index++; *\\/ *\/ */
/* 	/\* } while (str != NULL && index < max_val); *\/ */

/* 	str = get_next_line(fd); */
/* 	printf("%d: [%s]\n", index, str); */
/* 	close(fd); */
/* 	index++;	 */
/* 	g_n_max_read = -1; */
/* 	fd = open(filename, O_RDONLY); */
/* 	do { */
/* 		str = get_next_line(fd); */
/* 		printf("%d: [%s]\n", index, str); */
/* 		free(str); */
/* 		index++; */
/* 	} while (str != NULL && index < max_val); */

/*     return (0); */
/* } */

int	main(int argc, char *argv[])
{
	char	*filename;
	char	*str;
	int		index;
	int		max_val;
	int		fd;

	filename = "limits/04";
	if (argc == 2)
		filename = argv[1];
	printf("%s:\n", filename);
	fd = open(filename, O_RDONLY);
	index = 0;
	max_val = 15;
	while (1)
	{
		str = get_next_line(fd);
		printf("%s", str);
		free(str);
		if (str == NULL || index == max_val)
			break ;
		index++;
	}
	return (0);
}
