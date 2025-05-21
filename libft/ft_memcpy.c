/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhykim <junhykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 06:25:33 by junhykim          #+#    #+#             */
/*   Updated: 2024/10/20 06:34:03 by junhykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *destination, const void *source, size_t num)
{
	size_t			idx;
	unsigned char	*dp;
	unsigned char	*sp;

	dp = (unsigned char *)destination;
	sp = (unsigned char *)source;
	idx = 0;
	if (dp == sp)
		return (destination);
	while (idx < num)
	{
		dp[idx] = sp[idx];
		idx++;
	}
	return (destination);
}
