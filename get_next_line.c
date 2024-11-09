/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboutale <hboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:31:49 by hboutale          #+#    #+#             */
/*   Updated: 2024/11/09 19:05:19 by hboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_string_free(t_string *s, char *buffer)
{
	char	*temp;

	temp = s->data;
	if (buffer)
		free(buffer);
	if (s->len == 0)
	{
		free(temp);
		free(s);
		return (NULL);
	}
	free(s);
	return (temp);
}

char	*ft_strdup(char *src, size_t len)
{
	char	*res;
	size_t	i;

	if (len == (size_t)-1)
	{
		len = 0;
		while (src[len])
			len++;
	}
	i = 0;
	res = (char *)malloc(len + 1);
	if (res == NULL)
		return (NULL);
	while (i < len && src[i])
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
		return (false);
	*buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!*buffer)
		return (false);
	*s = create_string();
	if (!*s)
	{
		free(*buffer);
		*buffer = NULL;
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

	if (len == 0)
		return (NEW_LINE_FOUND);
	nl_idx = find(buffer, '\n');
	// printf("text: %s -- len:%zd -- cap: %zd\n", s->data, len, s->cap);
	if (nl_idx == -1)
	{
		if (!add(s, buffer, len))
			return (ERROR);
		return (NEW_LINE_NOT_FOUND);
	}
	if (!add(s, buffer, nl_idx + 1))
		return (ERROR);
	new_rest = ft_strdup(buffer + nl_idx + 1, -1);
	if (!new_rest)
		return (ERROR);
	if (*rest)
	{
		free(*rest);
		*rest = NULL;
	}
	*rest = new_rest;
	return (NEW_LINE_FOUND);
}

static void	*clean(char **buffer, t_string **s, char **rest)
{
	if (rest && *rest)
	{
		free(*rest);
		*rest = NULL;
	}
	if (buffer && *buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}
	if (s && *s)
	{
		free((*s)->data);
		free(*s);
		*s = NULL;
	}
	return (NULL);
}

static void	*process_rest(char **rest, t_string **s, char **buffer)
{
	ssize_t	nl_idx;
	char	*new_rest;

	if (!rest || !*rest)
		return (NULL);
	if (strlen(*rest) == 0)
		return (clean(NULL, NULL, rest));
	// printf("len: %zd - %s\n", strlen(*rest), *rest);
	nl_idx = find(*rest, '\n');
	if (nl_idx == -1)
	{
		if (!add(*s, *rest, -1))
			return (clean(buffer, s, rest));
		free(*rest);
		return (*rest = NULL);
	}
	if (!add(*s, *rest, nl_idx + 1))
		return (clean(buffer, s, rest));
	new_rest = ft_strdup(*rest + nl_idx + 1, -1);
	if (!new_rest)
		return (clean(buffer, s, rest));
	free(*rest);
	*rest = new_rest;
	return (*rest);
}

char	*get_next_line(int fd)
{
	static char	*rest = NULL;
	ssize_t		bytes;
	char		*buffer;
	t_string	*s;
	int			status;

	// printf("rest '%s' \n", rest);
	if (!init(fd, &buffer, &s))
		return (clean(&buffer, &s, &rest));
	if (process_rest(&rest, &s, &buffer))
		return (get_string_free(s, buffer));
	while (1)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
			return (clean(&buffer, &s, &rest));
		// printf("%zd\n", bytes);
		buffer[bytes] = '\0';
		status = process_line(buffer, bytes, s, &rest);
		if (status == ERROR)
			return (clean(&buffer, &s, &rest));
		if (status == NEW_LINE_FOUND || bytes == 0)
			return (get_string_free(s, buffer));
	}
	return (NULL);
}
