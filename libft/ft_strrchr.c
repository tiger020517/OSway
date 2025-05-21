/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhykim <junhykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 06:26:06 by junhykim          #+#    #+#             */
/*   Updated: 2024/10/20 07:39:12 by junhykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *string, int c)
{
	int		idx;
	char	tofind;

	tofind = (char)c;
	idx = 0;
	while (string[idx])
		idx++;
	while (idx >= 0)
	{
		if (string[idx] == tofind)
			return ((char *)string + idx);
		idx--;
	}
	return (0);
}
