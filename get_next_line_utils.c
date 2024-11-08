/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboutale <hboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:11:38 by hboutale          #+#    #+#             */
/*   Updated: 2024/11/08 12:29:25 by hboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_string	*create_string(size_t cap)
{
	t_string	*str;

	str = (t_string *)malloc(sizeof(t_string));
	if (!str)
		return (NULL);
	str->cap = 16;
	if (cap > str->cap)
		str->cap = cap;
	str->len = 0;
	str->data = (char *)malloc(sizeof(char) * str->cap);
	if (!str->data)
	{
		free(str);
		return (NULL);
	}
	str->data[0] = '\0';
	return (str);
}

static int	resize(t_string *str, size_t min_cap)
{
	size_t	new_cap;
	size_t	i;
	char	*new_data;

	if (str->cap >= min_cap)
		return (1);
	i = 0;
	new_cap = str->cap;
	while (new_cap < min_cap)
		new_cap *= 2;
	new_data = (char *)malloc(sizeof(char) * new_cap);
	if (!new_data)
		return (0);
	while (i < str->len + 1)
	{
		new_data[i] = str->data[i];
		i++;
	}
	free(str->data);
	str->data = new_data;
	return (1);
}

int	append_str(t_string *str, char *s, size_t len)
{
	size_t	new_len;
	size_t	i;

	new_len = str->len + len + 1;
	if (!resize(str, new_len))
		return (0);
	i = 0;
	while (i < len)
	{
		str->data[str->len++] = s[i];
		i++;
	}
	str->data[str->len] = '\0';
	return (1);
}

char	*get_string(t_string *str)
{
	char	*s;

	if (!str)
		return (NULL);
	s = str->data;
	free(str);
	return (s);
}

void	*free_str(t_string *s)
{
	if (!s)
		return (NULL);
	free(s->data);
	free(s);
	return (NULL);
}

size_t	ft_strlen(char *s)
{
	size_t	count;

	count = 0;
	while (s[count])
		count++;
	return (count);
}

char	*build_string(char *s)
{
	t_string	*str;
	size_t		s_len;

	s_len = ft_strlen(s);
	str = create_string(s_len);
	append_str(str, s, s_len);
	return (get_string(&str));
}
