/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhykim <junhykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 20:26:13 by junhykim          #+#    #+#             */
/*   Updated: 2024/11/02 23:34:43 by junhykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_printf(const char *str, ...);
static int	ft_printui(unsigned int data, char type, int num);
static int	ft_printp(void *data, char type, int num, int cnt);
static int	justice(char type, va_list args);
static int	ft_putnbrlen(int data);

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		idx;
	int		num;

	va_start (args, str);
	idx = 0;
	num = 0;
	while (str[idx])
	{
		if (str[idx] == '%')
		{
			num += justice(str[idx + 1], args);
			idx += 2;
		}
		else
		{
			ft_putchar_fd(str[idx++], 1);
			num++;
		}
	}
	va_end(args);
	return (num);
}

static int	justice(char type, va_list args)
{
	int		num;
	void	*tempp;

	num = 1;
	if (type == 'd' || type == 'i')
	{
		num = va_arg(args, int);
		num = ft_putnbrlen(num);
	}
	if (type == 'c')
		ft_putchar_fd(va_arg(args, int), 1);
	if (type == 'x' || type == 'X' || type == 'u')
		num = ft_printui(va_arg(args, unsigned int), type, 0);
	if (type == 's')
		num = ft_printp(va_arg(args, void *), type, 0, 0);
	if (type == 'p')
	{
		tempp = va_arg(args, void *);
		if (tempp)
			write (1, "0x", 2);
		num = ft_printp(tempp, type, 2, 0);
	}
	if (type == '%')
		ft_putchar_fd('%', 1);
	return (num);
}

static int	ft_printui(unsigned int data, char type, int num)
{
	if ((type == 'x' || type == 'X') && data >= 16)
		num = ft_printui(data / 16, type, num);
	if (type == 'u' && data >= 10)
		num = ft_printui(data / 10, type, num);
	if (type == 'x')
		ft_putchar_fd("0123456789abcdef"[data % 16], 1);
	if (type == 'X')
		ft_putchar_fd("0123456789ABCDEF"[data % 16], 1);
	if (type == 'u')
		ft_putchar_fd("0123456789"[data % 10], 1);
	return (num + 1);
}

static int	ft_printp(void *data, char type, int num, int cnt)
{
	unsigned long long	cut;

	if (type == 's')
	{
		if (!(char *)data)
		{
			write(1, "(null)", 6);
			return (6);
		}
		ft_putstr_fd((char *)data, 1);
		num = ft_strlen((const char *)data) - 1;
	}
	if (type == 'p')
	{
		if (cnt == 0 && !data)
		{
			write(1, "(nil)", 5);
			return (5);
		}
		cut = (unsigned long long)data;
		if (cut >= 16)
			num = ft_printp((void *)(cut / 16), 'p', num, cnt + 1);
		ft_putchar_fd("0123456789abcdef"[cut % 16], 1);
	}
	return (num + 1);
}

static	int	ft_putnbrlen(int data)
{
	int	num;

	if (data == -2147483648)
	{
		ft_putstr_fd("-2147483648", 1);
		return (11);
	}
	if (data < 0)
	{
		write(1, "-", 1);
		return (ft_putnbrlen(-data) + 1);
	}
	num = 1;
	if (data >= 10)
		num += ft_putnbrlen(data / 10);
	ft_putnbr_fd(data % 10, 1);
	return (num);
}
