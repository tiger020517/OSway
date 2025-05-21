/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhykim <junhykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 06:26:46 by junhykim          #+#    #+#             */
/*   Updated: 2024/10/20 06:26:46 by junhykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* s1 == haystack, s2 == needle*/
char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	s2len;
	size_t	i;

	if (!*s2)
		return ((char *)s1);
	s2len = 0;
	while (s2[s2len])
		s2len++;
	i = 0;
	while (i <= len - s2len && s1[i])
	{
		if (s1[i] == s2[0] && i + s2len <= len)
			if (!ft_strncmp((char *)(s1 + i), (char *)s2, s2len))
				return ((char *)(s1 + i));
		i++;
	}
	return (0);
}
