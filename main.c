/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marisous <marisous@student.42lisb...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 09:45:00 by marisous          #+#    #+#             */
/*   Updated: 2026/11/16 13:05:32 by marisous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main(int argc, char *argv[])
{
	char *filename = "text.txt";
	if (argc == 2)
		filename = argv[1];
	printf("%s:\n",filename);
	int fd = open(filename, O_RDONLY);

	char *str;
	int index;
	int max_val;
	
	index = 0;
	max_val = 10;
	do {
		str = get_next_line(fd);		
		printf("%s", str);
		free(str);
		index++;
	} while (str != NULL && index < max_val);

	printf("(end)\n");
    return (0);
}
