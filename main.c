/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marisous <marisous@student.42lisb...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 09:45:00 by marisous          #+#    #+#             */
/*   Updated: 2026/11/16 21:58:54 by marisous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int		read_count = 0;
int		n_max_read = -1;

ssize_t	__real_read(int fd, void *buf, size_t count);

ssize_t	__wrap_read(int fd, void *buf, size_t count)
{
	if (n_max_read != -1 && read_count + 1 > n_max_read)
		return (-1);
	read_count++;
	/* printf("Read count: [%d]: fd[%d], buf[%p: %s], count[%ld]\n", read_count, fd, buf, (char*)buf, count); */
	return (__real_read(fd, buf, count));
}

/* char *tests[18] = { */
/* 	"9",		// 1 + 1 +  */
/* 	"9\n",		// 2 + 1 +  */
/* 	"10",		// 1 + 1 +   */
/* 	"10\n",		// 2 + 1 +   */
/* 	"11",		// 1 + 1 +  */
/* 	"11\n",		// 2 + 1 +  */
/* 	"19",		// 1 + 1 +   */
/* 	"19\n",		// 2 + 1 +  */
/* 	"20",		// 1 + 1 +  */
/* 	"20\n",		// 2 + 1 +   */
/* 	"21",		// 1 + 1 +  */
/* 	"21\n",		// 2 + 1 +  */
/* 	"9\n9\n",	// 3 + 1 +  */
/* 	"9\n10",	// 2 + 1 +  */
/* 	"9\n10\n",	// 3 + 1 +  */
/* 	"10\n8\n",	// 3 + 1 +  */
/* 	"10\n9",	// 2 + 1 +   */
/* 	"10\n9\n"	// 3 + 1 +  */
/* 	}; */

/* int main(void) */
/* { */
/* 	n_max_read = 2; */
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
/* 	n_max_read = -1; */
/* 	fd = open(filename, O_RDONLY); */
/* 	do { */
/* 		str = get_next_line(fd); */
/* 		printf("%d: [%s]\n", index, str); */
/* 		free(str); */
/* 		index++; */
/* 	} while (str != NULL && index < max_val); */
	
/*     return (0); */
/* } */



int main(int argc, char *argv[])
{
	/* char *filename = "text_41wnl.txt"; */
	char *filename = "limits/04";
	if (argc == 2)
		filename = argv[1];
	/* printf("%s:\n",filename); */
	int fd = open(filename, O_RDONLY);

	char *str;
	int index;
	int max_val;
	
	index = 0;
	max_val = 15;
	while (1) {
		str = get_next_line(fd);
		printf("%s", str);
		if (str == NULL || index == max_val)
			break;			
		free(str);
		index++;
	} 

	/* printf("(end)\n"); */
    return (0);
}
