/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhykim <junhykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 06:26:06 by junhykim          #+#    #+#             */
/*   Updated: 2024/10/20 07:38:44 by junhykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *string, int c)
{
	int		idx;
	char	tofind;

	tofind = (char)c;
	idx = 0;
	while (string[idx])
	{
		if (string[idx] == tofind)
			return ((char *)string + idx);
		idx++;
	}
	if (string[idx] == tofind)
		return ((char *)string + idx);
	return (0);
}
