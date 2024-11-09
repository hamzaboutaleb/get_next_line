/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboutale <hboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:10:55 by hboutale          #+#    #+#             */
/*   Updated: 2024/11/09 18:48:26 by hboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("only_nl.txt", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
		{
			printf("%s", line);
			break ;
		}
		printf("%s", line);
	}
}

//-------------- TEST T_STRING -----------------
// int	main(void)
// {
// 	t_string *s;
// 	int i;

// 	i = 0;
// 	s = create_string();
// 	if (!s)
// 		return (1);
// 	printf("[%d] -> %s\n", i++, s->data);
// 	add(s, "hello", 5);
// 	printf("[%d] -> %s\n", i++, s->data);
// 	if (!add(s, " welcome", -1))
// 		return (1);
// 	printf("[%d] -> %s\n", i++, s->data);
// }