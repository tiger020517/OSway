/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhykim <junhykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 22:47:33 by junhykim          #+#    #+#             */
/*   Updated: 2025/01/08 15:10:09 by junhykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	gnl_bufchr(t_safe buffer, char c)
{
	int	idx;

	idx = -1;
	if (buffer.type)
	{
		while (buffer.data[++idx])
		{
			if (buffer.data[idx] == c)
				return (idx + 1);
		}
		if (c == '\0')
			return (idx + 1);
	}
	else
	{
		while (++idx < BUFFER_SIZE + 1 && buffer.data[idx])
			if (buffer.data[idx] == c)
				return (idx + 1);
	}
	return (0);
}

int	gnl_strlen(char *str)
{
	size_t	idx;

	if (!str)
		return (0);
	idx = 0;
	while (str[idx])
		idx++;
	return (idx);
}

int	gnl_bufflen(t_safe buffer)
{
	size_t	idx;

	if (!buffer.type)
		return (BUFFER_SIZE);
	if (!buffer.data)
		return (0);
	idx = 0;
	while (buffer.data[idx])
		idx++;
	return (idx);
}

char	*gnl_plant(char *s1, t_safe buffer, int n_len)
{
	char	*temp;
	int		len;
	int		idx;
	int		sidx;

	len = n_len + gnl_strlen(s1);
	temp = (char *)malloc(len);
	if (!temp)
		return (free(s1), NULL);
	idx = -1;
	sidx = gnl_strlen(s1);
	while (++idx < sidx && s1[idx])
		temp[idx] = s1[idx];
	sidx = 0;
	while (idx < len - 1)
		temp[idx++] = buffer.data[sidx++];
	temp[idx] = '\0';
	free(s1);
	return (temp);
}
