/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboutale <hboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:31:46 by hboutale          #+#    #+#             */
/*   Updated: 2024/11/10 22:50:49 by hboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*create_list(void)
{
	t_list	*list;

	list = (t_list *)malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->head = NULL;
	list->tail = NULL;
	list->reach_end = FALSE;
	list->line_length = 0;
	list->size = 0;
	return (list);
}

t_bool	push_back(t_list **list)
{
	t_buffer	*buffer;

	if (!list || !*list)
		return (FALSE);
	buffer = create_buffer();
	if (!buffer)
		return (list_free(list) && FALSE);
	(*list)->size++;
	if ((*list)->head == NULL)
	{
		(*list)->head = buffer;
		(*list)->tail = buffer;
		return (TRUE);
	}
	(*list)->tail->next = buffer;
	(*list)->tail = buffer;
	return (TRUE);
}

void	*list_free(t_list **list)
{
	t_buffer	*curr;
	t_buffer	*next;

	if (!list || !*list)
		return (NULL);
	if (!list || !(*list)->head)
		return (NULL);
	curr = (*list)->head;
	while (curr)
	{
		next = curr->next;
		if (curr->buffer)
			free(curr->buffer);
		free(curr);
		curr = next;
	}
	free(*list);
	*list = NULL;
	return (NULL);
}

void	delete_first(t_list *list)
{
	t_buffer	*deleted;

	if (!list || !list->head)
		return ;
	deleted = list->head;
	list->head = list->head->next;
	if (deleted->buffer)
		free(deleted->buffer);
	free(deleted);
	list->size--;
	if (list->size == 0)
	{
		list->head = NULL;
		list->tail = NULL;
	}
}

t_buffer	*create_buffer(void)
{
	t_buffer	*buffer;

	buffer = (t_buffer *)malloc(sizeof(t_buffer));
	if (!buffer)
		return (NULL);
	buffer->buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer->buffer)
	{
		free(buffer);
		return (NULL);
	}
	buffer->len = 0;
	buffer->next = NULL;
	buffer->nl_pos = -1;
	buffer->cursor = 0;
	return (buffer);
}
