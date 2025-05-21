/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhykim <junhykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 06:25:37 by junhykim          #+#    #+#             */
/*   Updated: 2024/10/20 08:00:31 by junhykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t count)
{
	size_t	len;

	if (!dest && !src)
		return (NULL);
	len = 0;
	if (src < dest)
	{
		len = count;
		while (len > 0)
		{
			len--;
			((unsigned char *)dest)[len] = ((unsigned char *)src)[len];
		}
	}
	else
	{
		len = 0;
		while (len < count)
		{
			((unsigned char *)dest)[len] = ((unsigned char *)src)[len];
			len++;
		}
	}
	return (dest);
}
