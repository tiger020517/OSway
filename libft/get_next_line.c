/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhykim <junhykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 22:47:27 by junhykim          #+#    #+#             */
/*   Updated: 2025/01/08 14:52:20 by junhykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	static t_safe	buffer;
	char			*go;

	if (BUFFER_SIZE <= 0)
		return (0);
	go = 0;
	if (!buffer.type)
		if (!buffer_read(fd, &buffer))
			return (NULL);
	while (!gnl_bufchr(buffer, '\n'))
	{
		go = buffer_plant(go, buffer);
		buffer = buffer_clear(buffer);
		if (!buffer_read(fd, &buffer))
		{
			if (go)
				return (go);
			return (NULL);
		}
	}
	go = buffer_plant(go, buffer);
	buffer = buffer_set(buffer);
	return (go);
}

int	buffer_read(int fd, t_safe *buffer)
{
	ssize_t	bytesread;

	buffer->data = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer->data)
		return (0);
	buffer->data[0] = '\0';
	bytesread = read(fd, buffer->data, BUFFER_SIZE);
	if (bytesread < 0 || (bytesread == 0 && !*buffer->data))
		return (free(buffer->data), buffer->data = 0, 0);
	buffer->data[bytesread] = '\0';
	return (1);
}

//n_len is \n or \0 index so + 1 for null
char	*buffer_plant(char *go, t_safe buffer)
{
	char	*temp;
	int		n_len;
	int		idx;

	if (gnl_bufchr(buffer, '\n'))
		n_len = gnl_bufchr(buffer, '\n') + 1;
	else if (gnl_bufchr(buffer, '\0'))
		n_len = gnl_bufchr(buffer, '\0') + 1;
	else
		n_len = BUFFER_SIZE + 1;
	if (go)
		return (gnl_plant(go, buffer, n_len));
	else
	{
		idx = -1;
		temp = (char *)malloc(n_len);
		while (++idx < n_len - 1)
			temp[idx] = buffer.data[idx];
		temp[idx] = '\0';
		return (temp);
	}
}

t_safe	buffer_clear(t_safe buffer)
{
	buffer.type = 0;
	free(buffer.data);
	buffer.data = 0;
	return (buffer);
}

t_safe	buffer_set(t_safe buffer)
{
	char	*temp;
	int		ns;
	int		idx;
	int		len;

	if (gnl_bufchr(buffer, '\n'))
	{
		len = gnl_bufflen(buffer);
		ns = gnl_bufchr(buffer, '\n');
		idx = -1;
		temp = (char *)malloc(len - ns + 1);
		if (!temp)
			return (free(buffer.data), buffer.data = 0,
				buffer.type = 0, buffer);
		while (++idx + ns < len)
			temp[idx] = buffer.data[idx + ns];
		temp[idx] = '\0';
		if (!buffer.data[ns])
			return (free(buffer.data), free(temp),
				buffer.data = 0, buffer.type = 0, buffer);
		buffer.type = 1;
		return (free(buffer.data), buffer.data = temp, buffer);
	}
	else
		return (free(buffer.data), buffer.data = 0, buffer.type = 0, buffer);
}
