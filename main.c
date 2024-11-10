/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboutale <hboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:10:55 by hboutale          #+#    #+#             */
/*   Updated: 2024/11/10 13:33:27 by hboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	main(void)
{
	int fd;
	char *line;

	fd = open("hello.txt", O_RDONLY);

	do
	{
		line = get_next_line(fd);
		printf("%s", line);
	} while (line);
}