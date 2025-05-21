/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhykim <junhykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 06:24:35 by junhykim          #+#    #+#             */
/*   Updated: 2024/10/20 06:43:31 by junhykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_char(char *s, unsigned int number, long int len)
{
	while (number > 0)
	{
		s[len--] = 48 + (number % 10);
		number = number / 10;
	}
	return (s);
}

static long int	ft_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char				*s;
	long int			len;
	unsigned int		number;
	int					sign;

	sign = 1;
	len = ft_len(n);
	s = (char *)malloc(sizeof(char) * (len + 1));
	if (!(s))
		return (NULL);
	s[len--] = '\0';
	if (n == 0)
		s[0] = '0';
	if (n < 0)
	{
		sign *= -1;
		number = n * -1;
		s[0] = '-';
	}
	else
		number = n;
	s = ft_char(s, number, len);
	return (s);
}

/* #include "libft.h"

static int		ft_numlen(int n);

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		flag;

	flag = 1;
	len = ft_numlen(n);
	str = (char *)malloc(n + 2);
	str[0] = '-';
	str[n + 1] = '\0';
	if (n == -2147483648)
	{
		ft_strlcat(str, "2147483648", (unsigned int)12);
		return (str);
	}
	if (n < 0)
	{
		n = -n;
		flag = 0;
	}
	while (len > 0)
	{
		str[len--] = (n % 10) + '0';
		n /= 10;
	}
	return (&str[flag]);
}

static int	ft_numlen(int n)
{
	int	len;

	if (n == 0)
		return (1);
	len = 0;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}
 */