/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhykim <junhykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 06:25:52 by junhykim          #+#    #+#             */
/*   Updated: 2024/10/20 06:25:52 by junhykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	wow(int nb, int fd);

void	ft_putnbr_fd(int nb, int fd)
{
	if (nb < 0)
	{
		write(fd, "-", 1);
		nb *= -1;
	}
	else if (nb == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	if (nb == -2147483648)
		write(fd, "2147483648", 10);
	else
	{
		wow(nb, fd);
	}
	return ;
}

static void	wow(int nb, int fd)
{
	if (nb == 0)
		return ;
	wow (nb / 10, fd);
	ft_putchar_fd (nb % 10 + 48, fd);
}
