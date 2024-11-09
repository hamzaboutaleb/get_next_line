/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboutale <hboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:31:49 by hboutale          #+#    #+#             */
/*   Updated: 2024/11/09 15:33:39 by hboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_string_free(t_string *s, char *buffer)
{
	char	*temp;

	temp = s->data;
	free(s);
	free(buffer);
	return (temp);
}

char	*ft_strdup(char *src, size_t len)
{
	char	*res;
	int		i;

	i = 0;
	res = (char *)malloc(len + 1);
	if (res == NULL)
		return (NULL);
	while (src[i] && i < len)
	{
		res[i] = src[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

static t_bool	init(int fd, char **buffer, t_string **s)
{
	*buffer = NULL;
	*s = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	*buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!*buffer)
		return (false);
	*s = create_string();
	if (!*s)
	{
		free(buffer);
		return (false);
	}
	return (true);
}

ssize_t	find(char *haystack, char needle)
{
	ssize_t	i;

	i = 0;
	while (haystack[i] && haystack[i] != needle)
		i++;
	if (!haystack[i])
		return (-1);
	return (i);
}

static int	process_line(char *buffer, ssize_t len, t_string *s, char **rest)
{
	ssize_t	nl_idx;
	char	*new_rest;

	nl_idx = find(buffer, '\n');
	if (nl_idx == -1)
	{
		if (!add(s, buffer, len))
			return (ERROR);
		return (NEW_LINE_NOT_FOUND);
	}
	if (!add(s, buffer + nl_idx + 1, -1))
		return (ERROR);
	new_rest = ft_strdup(buffer, nl_idx);
	if (!new_rest)
		return (ERROR);
	if (*rest)
	{
		free(*rest);
		*rest = NULL;
	}
	*new_rest = new_rest;
	return (NEW_LINE_FOUND);
}

static void	*clean(char *buffer, t_string *s, char **rest)
{
	if (*rest)
	{
		free(rest);
		*rest = NULL;
	}
	if (buffer)
		free(buffer);
	if (s)
	{
		free(s->data);
		free(s);
	}
	return (NULL);
}

static int process_rest(char **rest, t_string) {
	
}

static char	*get_next_line(int fd)
{
	static char	*rest = NULL;
	ssize_t		bytes;
	char		*buffer;
	t_string	*s;
	int			status;

	if (!init(fd, &buffer, &s))
		return (clean(buffer, s, *rest));
	while (1)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		buffer[bytes] = '\0';
		status = process_line(buffer, bytes, s, &rest);
		if (status == ERROR)
			return (clean(buffer, s, &rest));
		if (status == NEW_LINE_FOUND)
			return (get_string_free(s, buffer));
	}
	return (NULL);
}
