/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboutale <hboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:11:40 by hboutale          #+#    #+#             */
/*   Updated: 2024/11/08 12:37:15 by hboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	find(char *s, char c)
{
	ssize_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*process_line(t_string *s, char *remain_str)
{
	t_string	*str;

	str = create_string(BUFFER_SIZE);
	if (!str)
		return (NULL);
	return (get_string(&s));
}

char	*read_line(int fd, char *buffer, t_string *str)
{
	ssize_t		bytes;
	ssize_t		idx;
	static char	*remain = NULL;

	while (1)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		buffer[bytes] = '\0';
		if (bytes <= 0)
			break ;
		idx = find(buffer, '\n');
		if (idx == 0)
			append_str(str, buffer, bytes);
		else
		{
			append_str(str, buffer, idx + 1);
			remain = build_string(&buffer[idx + 1]);
			return (get_string(str));
		}
	}
	if (bytes == 0 && str->len > 0)
		return (get_string(str));
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	t_string	*str;
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = create_string(BUFFER_SIZE);
	if (!str)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (free_str(&str));
	result = read_line(fd, buffer, str);
	free(buffer);
	free_str(str);
	return (result);
}

/*
		3   5
h e l l o 0
		^   ^
5-3 = 2
*/