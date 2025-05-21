/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhykim <junhykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 06:26:54 by junhykim          #+#    #+#             */
/*   Updated: 2024/10/20 06:26:54 by junhykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*str;

	str = 0;
	if (s1 && set)
	{
		end = ft_strlen((char *)s1);
		start = 0;
		while (s1[start] && ft_strchr(set, s1[start]))
			start++;
		while (s1[end - 1] && ft_strchr(set, s1[end - 1]) && end > start)
			end--;
		str = (char *)malloc(end - start + 1);
		if (str)
			ft_strlcpy(str, (char *)(s1 + start), end - start + 1);
	}
	return (str);
}
