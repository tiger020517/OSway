/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhykim <junhykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 06:25:28 by junhykim          #+#    #+#             */
/*   Updated: 2024/10/20 06:31:40 by junhykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	unsigned char	*op;
	unsigned char	*tp;
	size_t			idx;

	op = (unsigned char *)ptr1;
	tp = (unsigned char *)ptr2;
	idx = 0;
	while (idx < num)
	{
		if (op[idx] != tp[idx])
			return ((unsigned char)op[idx] - (unsigned char)tp[idx]);
		idx++;
	}
	return (0);
}
