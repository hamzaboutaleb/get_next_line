/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboutale <hboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:31:49 by hboutale          #+#    #+#             */
/*   Updated: 2024/11/10 22:48:56 by hboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	find(char *buffer, char c)
{
	ssize_t	i;

	i = 0;
	while (buffer[i] && buffer[i] != c)
		i++;
	if (buffer[i] == c)
		return (i);
	return (-1);
}

t_list	*read_file(int fd, t_list **list)
{
	if (!list && !*list)
		return (NULL);
	while (1)
	{
		if (list && !push_back(list))
			return (NULL);
		(*list)->tail->len = read(fd, (*list)->tail->buffer, BUFFER_SIZE);
		if ((*list)->tail->len == -1)
			return (list_free(list));
		(*list)->tail->buffer[(*list)->tail->len] = '\0';
		if ((*list)->tail->len == 0)
		{
			(*list)->reach_end = TRUE;
			return ((*list));
		}
		(*list)->tail->nl_pos = find((*list)->tail->buffer, '\n');
		if ((*list)->tail->nl_pos != (size_t)(-1))
		{
			(*list)->line_length += (*list)->tail->nl_pos + 1;
			return ((*list));
		}
		(*list)->line_length += (*list)->tail->len;
	}
}

char	*ft_line(t_list **list)
{
	char		*line;
	t_buffer	*cur;
	size_t		i;

	i = 0;
	if ((*list)->line_length == 0)
		return (list_free(list));
	cur = (*list)->head;
	line = (char *)malloc(sizeof(char) * ((*list)->line_length + 1));
	if (!line)
		return (list_free(list));
	while (cur && i < (*list)->line_length)
	{
		cur = (*list)->head;
		while (i < (*list)->line_length && cur->cursor < (size_t)cur->len)
		{
			line[i++] = cur->buffer[cur->cursor++];
		}
		if ((size_t)cur->len == cur->cursor && cur->len > 0)
			delete_first(*list);
	}
	line[i] = '\0';
	(*list)->line_length = 0;
	return (line);
}

char	*get_rest(t_list **list)
{
	t_buffer	*buf;

	if (!list || !*list)
		return (NULL);
	if ((*list)->size == 0)
		return (NULL);
	buf = (*list)->head;
	buf->nl_pos = find(buf->buffer + buf->cursor, '\n');
	if (buf->nl_pos != (size_t)-1)
	{
		(*list)->line_length = (buf->cursor + buf->nl_pos + 1) - buf->cursor;
	}
	else
	{
		(*list)->line_length = buf->len - buf->cursor;
		return (NULL);
	}
	return (ft_line(list));
}

char	*get_next_line(int fd)
{
	static t_list	*list;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!list)
	{
		list = create_list();
		if (!list)
			return (NULL);
	}
	line = get_rest(&list);
	if (line)
		return (line);
	list = read_file(fd, &list);
	if (list && list->reach_end == TRUE && list->size == 1)
		return (list_free(&list));
	if (!list)
		return (NULL);
	line = ft_line(&list);
	return (line);
}
