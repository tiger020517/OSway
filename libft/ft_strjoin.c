/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhykim <junhykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 06:26:18 by junhykim          #+#    #+#             */
/*   Updated: 2024/10/20 06:26:18 by junhykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*go;
	size_t	idx;

	len = ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1;
	go = (char *)malloc(sizeof(char) * len);
	if (!go)
		return (NULL);
	idx = 0;
	while (*s1)
		go[idx++] = *(s1++);
	while (*s2)
		go[idx++] = *(s2++);
	go[idx] = '\0';
	return (go);
}
