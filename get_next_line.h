/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboutale <hboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:11:35 by hboutale          #+#    #+#             */
/*   Updated: 2024/11/07 18:33:04 by hboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_array
{
	char	*data;
	size_t	size;
	size_t	cap;
}			t_array;

char		*get_next_line(int fd);
t_array		*create_array(t_array **array_ptr);
int			insert_char(t_array **array, char c);
void		*free_array(t_array **arr);

#endif