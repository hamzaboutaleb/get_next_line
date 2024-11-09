/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboutale <hboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:31:46 by hboutale          #+#    #+#             */
/*   Updated: 2024/11/09 19:00:51 by hboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_string	*create_string(void)
{
	t_string	*s;

	s = (t_string *)malloc(sizeof(t_string));
	if (!s)
		return (NULL);
	s->cap = 1;
	s->len = 0;
	s->data = (char *)malloc(sizeof(char) * s->cap);
	if (!s->data)
	{
		free(s);
		return (NULL);
	}
	s->data[0] = '\0';
	return (s);
}

static t_bool	resize(t_string *s, size_t new_cap)
{
	char	*new_str;
	size_t	i;

	if (new_cap == 0)
		return (false);
	new_str = (char *)malloc(sizeof(char) * new_cap);
	if (new_str == NULL)
		return (false);
	i = 0;
	while (i <= s->len && i < new_cap)
	{
		new_str[i] = s->data[i];
		i++;
	}
	free(s->data);
	s->data = new_str;
	s->cap = new_cap;
	return (true);
}

t_bool	add(t_string *s, char *str, size_t len)
{
	size_t	i;

	if (len == (size_t)-1)
	{
		len = 0;
		while (str[len])
			len++;
	}
	// printf("\nnew malloc size: %zd\n", s->cap );
	if (!resize(s, s->cap + len))
		return (false);
	i = 0;
	while (str[i] && i < len)
		s->data[s->len++] = str[i++];
	s->data[s->len] = '\0';
	return (true);
}
