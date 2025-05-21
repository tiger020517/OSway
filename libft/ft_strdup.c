/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhykim <junhykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 06:26:10 by junhykim          #+#    #+#             */
/*   Updated: 2024/10/20 07:41:14 by junhykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *string)
{
	int		len;
	char	*dup;

	len = ft_strlen((char *)string) + 1;
	dup = (char *)malloc(sizeof(char) * len);
	if (!dup)
		return (NULL);
	len = 0;
	while (string[len])
	{
		dup[len] = string[len];
		len++;
	}
	dup[len] = '\0';
	return (dup);
}
