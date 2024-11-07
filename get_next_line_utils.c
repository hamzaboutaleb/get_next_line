/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboutale <hboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:11:38 by hboutale          #+#    #+#             */
/*   Updated: 2024/11/07 18:32:47 by hboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	resize(t_array *arr, size_t new_size)
{
	char	*data;
	size_t	i;

	if (!arr)
		return (0);
	data = (char *)malloc(sizeof(char) * new_size);
	if (!data)
		return (0);
	i = 0;
	while (i < arr->size)
	{
		data[i] = arr->data[i];
		i++;
	}
	free(arr->data);
	arr->data = data;
	arr->cap = data;
	return (1);
}

t_array	*create_array(t_array **array_ptr)
{
	t_array	*array;

	if (!array_ptr)
		return (NULL);
	if (*array_ptr)
		free_array(array_ptr);
	array = (t_array *)malloc(sizeof(t_array));
	if (!array)
		return (NULL);
	else
	{
		array->cap = 32;
		array->size = 0;
		array->data = (char *)malloc(sizeof(char) * array->cap);
	}
	return (array);
}

char	*insert_str(t_array **array, char *s, size_t size)
{
	size_t	diff;
	int		is_resized;
	t_array	*arr;

	if (!s || !array)
		return (NULL);
	arr = *array;
	while (size--)
	{
		if (arr->size >= arr->cap && !resize(arr, arr->cap * 2))
			return (free_array(array));
	}
	return (arr->data);
}

int	insert_char(t_array **array, char c)
{
	t_array	*arr;

	if (!array || !*array)
		return (0);
	arr = *array;
	if (arr->size >= arr->cap && !resize(arr, arr->cap * 2))
	{
		free_array(array);
		return (0);
	}
	arr->data[arr->size++] = c;
	return (1);
}

void	*free_array(t_array **arr)
{
	free((*arr)->data);
	free(*arr);
	*arr = NULL;
	return (NULL);
}