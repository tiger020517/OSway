/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhykim <junhykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 06:26:14 by junhykim          #+#    #+#             */
/*   Updated: 2024/10/20 06:29:27 by junhykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	idx;
	int	len;

	len = ft_strlen(s);
	idx = 0;
	while (idx < len)
	{
		f(idx, &s[idx]);
		idx++;
	}
}
