/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhykim <junhykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 06:26:37 by junhykim          #+#    #+#             */
/*   Updated: 2024/10/20 06:29:34 by junhykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*news;
	int		idx;

	news = (char *)malloc(ft_strlen((char *)s) + 1);
	if (!news)
		return (NULL);
	idx = 0;
	while (s[idx])
	{
		news[idx] = f(idx, s[idx]);
		idx++;
	}
	news[idx] = '\0';
	return (news);
}
