/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhykim <junhykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 06:24:07 by junhykim          #+#    #+#             */
/*   Updated: 2024/10/20 06:31:59 by junhykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total_size;
	void	*ptr;
	size_t	max_value;

	max_value = (size_t)(-1);
	if (size != 0 && count > max_value / size)
		return (NULL);
	total_size = count * size;
	ptr = malloc(total_size);
	if (!ptr)
		return (0);
	ft_memset(ptr, 0, total_size);
	return (ptr);
}
