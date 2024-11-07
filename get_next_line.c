/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboutale <hboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:11:40 by hboutale          #+#    #+#             */
/*   Updated: 2024/11/07 18:48:08 by hboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_array	*arr = NULL;
	static size_t	start = 0;
	char			*buffer[BUFFER_SIZE];
	size_t			i;
	size_t			read_bytes;

	start = 0;
	start = 0;
	i = 0;
	arr = create_array(arr);
	if (!arr || fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_bytes = read(fd, buffer, BUFFER_SIZE);
	while (read_bytes > 0)
	{
		while (i < read_bytes && buffer[i] != '\n')
		{
			if (insert_char(&arr, buffer[i]))
				return (NULL);
			i++;
		}
		read_bytes = read(fd, buffer, BUFFER_SIZE);
	}
	if (read_bytes < 0)
		return (free_array(&arr));
	return (NULL);
}
