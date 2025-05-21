/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhykim <junhykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 06:26:58 by junhykim          #+#    #+#             */
/*   Updated: 2024/10/20 08:09:19 by junhykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	slen;
	size_t	finish;

	if (!s)
		return (0);
	slen = ft_strlen((char *)s);
	if (start >= slen)
		return (ft_strdup(""));
	finish = slen - start;
	if (finish > len)
		finish = len;
	str = (char *)malloc(finish + 1);
	if (!str)
		return (0);
	ft_strlcpy(str, (char *)(s + start), finish + 1);
	return (str);
}
