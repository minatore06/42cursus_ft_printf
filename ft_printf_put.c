/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_put.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:43:08 by scaiazzo          #+#    #+#             */
/*   Updated: 2022/11/22 11:43:11 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	ft_putstr(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '%' && s[i + 1])
		{
			if (s[i + 1] == '%')
				ft_putchar('%');
			else
				return (i);
			i += 2;
			continue ;
		}
		ft_putchar(s[i]);
		i++;
	}
	return (i);
}

void	ft_putpad(int npad, int pad)
{
	while (npad-- > 0)
		ft_putchar((char)pad);
}

void	ft_putnbrbase(long n, int base, int uc)
{
	char	c;

	if (n < 0)
	{
		ft_putchar('-');
		n *= -1;
	}
	if (n > base - 1)
		ft_putnbrbase(n / base, base, uc);
	if (n % base > 9)
	{
		c = n % base - 10 + 97;
		if (uc)
			c -= 32;
	}
	else
		c = n % base + 48;
	ft_putchar_fd(c, 1);
}

void	ft_putunnbrbase(unsigned long n, unsigned int base, int uc)
{
	char	c;

	if (n > base - 1)
		ft_putnbrbase(n / base, base, uc);
	if (n % base > 9)
	{
		c = n % base - 10 + 97;
		if (uc)
			c -= 32;
	}
	else
		c = n % base + 48;
	ft_putchar_fd(c, 1);
}
