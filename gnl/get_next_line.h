/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhykim <junhykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 03:13:15 by junhykim          #+#    #+#             */
/*   Updated: 2025/01/08 15:13:08 by junhykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_safe {
	char	*data;
	int		type;
}	t_safe;

int		gnl_bufchr(t_safe buffer, char c);
int		gnl_strlen(char *str);
int		gnl_bufflen(t_safe buffer);
char	*gnl_plant(char *s1, t_safe buffer, int n_len);
char	*get_next_line(int fd);
int		buffer_read(int fd, t_safe *buffer);
char	*buffer_plant(char *go, t_safe buffer);
t_safe	buffer_clear(t_safe buffer);
t_safe	buffer_set(t_safe buffer);

#endif
