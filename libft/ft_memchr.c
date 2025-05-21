/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhykim <junhykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 06:25:24 by junhykim          #+#    #+#             */
/*   Updated: 2024/10/20 06:25:24 by junhykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *buf, int c, size_t count)
{
	unsigned char	*bp;
	unsigned char	tofind;
	size_t			idx;

	bp = (unsigned char *)buf;
	tofind = (unsigned char)c;
	idx = 0;
	while (idx < count)
	{
		if (bp[idx] == tofind)
			return (&bp[idx]);
		idx++;
	}
	return (0);
}
