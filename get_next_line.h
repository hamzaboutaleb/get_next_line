/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboutale <hboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:11:35 by hboutale          #+#    #+#             */
/*   Updated: 2024/11/10 20:45:22 by hboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# define TRUE 1
# define FALSE 0
# define NEW_LINE_FOUND 0
# define NEW_LINE_NOT_FOUND 1
# define ERROR 2

typedef int			t_bool;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_buffer
{
	char			*buffer;
	size_t			nl_pos;
	ssize_t			len;
	size_t			cursor;
	struct s_buffer	*next;
}					t_buffer;

typedef struct s_list
{
	t_buffer		*head;
	t_buffer		*tail;
	int				reach_end;
	size_t			line_length;
	size_t			size;
}					t_list;

char				*get_next_line(int fd);
t_buffer			*create_buffer(void);
t_bool				push_back(t_list *list);
void				*list_free(t_list *list);
void				delete_first(t_list *list);
t_list				*create_list(void);
#endif
