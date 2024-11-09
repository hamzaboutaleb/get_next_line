/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboutale <hboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:11:35 by hboutale          #+#    #+#             */
/*   Updated: 2024/11/09 14:56:25 by hboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define true 1
# define false 0
# define NEW_LINE_FOUND 0
# define NEW_LINE_NOT_FOUND 1
# define ERROR 2
typedef int	t_bool;
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_string
{
	char	*data;
	size_t	len;
	size_t	cap;
}			t_string;

char		*get_next_line(int fd);
t_string	*create_string(void);
t_bool		add(t_string *s, char *str, size_t len);
#endif
