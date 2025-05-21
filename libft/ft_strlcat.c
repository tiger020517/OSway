/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhykim <junhykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 06:26:24 by junhykim          #+#    #+#             */
/*   Updated: 2024/10/20 06:26:25 by junhykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int				ft_strlen(char *str);

unsigned int	ft_strlcat(char *dest, char *src, unsigned int size)
{
	unsigned int	dlen;
	unsigned int	srclen;
	unsigned int	idx;
	unsigned int	sidx;

	dlen = ft_strlen(dest);
	srclen = ft_strlen(src);
	if (size == 0 || size <= dlen)
		return (size + srclen);
	idx = 0;
	while (idx < dlen)
		idx++;
	sidx = 0;
	while (idx < size - 1 && sidx < srclen)
		dest[idx++] = src[sidx++];
	dest[idx] = '\0';
	return (dlen + srclen);
}

static int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}
