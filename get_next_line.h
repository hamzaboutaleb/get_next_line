/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboutale <hboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:11:35 by hboutale          #+#    #+#             */
/*   Updated: 2024/11/08 12:29:35 by hboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 500
# endif

typedef struct s_string
{
	char	*data;
	size_t	len;
	size_t	cap;
}			t_string;

t_string	*create_string(size_t cap);
char		*get_next_line(int fd);
int			append_str(t_string *str, char *s, size_t len);
char		*get_string(t_string *str);
void		*free_str(t_string *s);
char		*build_string(char *s);
size_t		ft_strlen(char *s);
#endif