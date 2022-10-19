/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 15:18:38 by scaiazzo          #+#    #+#             */
/*   Updated: 2022/10/11 15:45:52 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include "libftprintf.h"
#include "libft/libft.h"

#include <stdio.h>

//void	ft_putchar_fd(char c, int fd)
//void	ft_putstr_fd(char *s, int fd)
//void	ft_putnbr_fd(int n, int fd)


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
			continue;
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

int	nbrlen(long n, int base)
{
	int	ndig;

	ndig = 1;
	if (n < 0)
	{
		ndig++;
		n *= -1;
	}
	while (n > base - 1)
	{
		n /= base;
		ndig++;
	}
	return (ndig);
}

int	max(int n1, int n2)
{
	if (n1 > n2)
		return (n1);
	return (n2);
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

void	managenbr(long n, int base, int uc, int *npad, t_flags flags)
{
	int		meno;
	char	pad;

	pad = (char) flags.pad;
	meno = flags.meno;
	if (flags.numsign && base == 16 && n)
	{
		ft_putchar('0');
		if (uc)
			ft_putchar('X');
		else
			ft_putchar('x');	}
	if (n < 0)
	{
		ft_putchar('-');
		n *= -1;
	}
	if (!meno)
	{
		ft_putpad(npad[0] - max(npad[1], nbrlen(n, 10)), pad);
		ft_putpad(npad[1] - nbrlen(n, 10), '0');
	}
	else
		ft_putpad(npad[1] - nbrlen(n, 10), '0');
	ft_putnbrbase(n, base, uc);
	if (meno)
		ft_putpad(npad[0] - max(npad[1], nbrlen(n, 10)), ' ');
}

char	*ptrtostr(long ptr)
{
	int		i;
	int	tmp;
	char	*str;

	str = malloc(sizeof(char) * 15);
	str[14] = '\0';
	str[1] = 'x';
	str[0] = '0';
	i = 13;
	while (i >=2)
	{
		tmp = ptr % 16;
		if (tmp > 9)
			str[i] = tmp - 10 + 97;
		else
			str[i] = tmp + 48;
		ptr /= 16;
		i--;
	}
	return (str);
}

int	ft_printf(const char *str, ...)
{
	int		npad[2];
	int		i;
	t_flags	flags;
	long	n;
	va_list arg_ptr;
	char	*strvar;

	i = 0;
	va_start(arg_ptr, str);	
	while (*(str + i))
	{
		npad[0] = 0;
		npad[1] = 0;
		flags.pad = 32;
		flags.meno = 0;
		i += ft_putstr((char *)str + i);
		if (str[i] == '%')
		{
			if(str[i + 1] == '#')
			{
				flags.numsign = 1;
				i++;
			}
			if (str[i + 1] == '-' || str[i + 2] == '-')
			{
				flags.meno = 1;
				if (str[i + 1] == '-')
					i++;
				else if (str[i + 2] == '-')
					i += 2;
			}
			else if (str[i + 1] == '0')
			{
				flags.pad = 48;
				i++;
			}
			if(str[i + 1] == '#')
			{
				flags.numsign = 1;
				i++;
			}
			while (ft_isdigit(str[i + 1]))
			{
				npad[0] *= 10;
				npad[0] += str[i + 1] - 48;
				i++;
			}
			if (str[i + 1] == '.')
			{
				i++;
				while (ft_isdigit(str[i + 1]))
				{
					npad[1] *= 10;
					npad[1] += str[i + 1] - 48;
					i++;
				}
				flags.punto = 1;
			}
			if (str[i + 1] == 'c' || str[i + 1] == 's' || str[i + 1] == 'p'
				|| str[i + 1] == 'd' || str[i + 1] == 'i' || str[i + 1] == 'u'
				|| str[i + 1] == 'x' || str[i + 1] == 'X')
			{
				if (str[i + 1] == 'c')
				{
					if (!flags.meno)
						ft_putpad(npad[0] - 1, flags.pad);
					ft_putchar((char)va_arg(arg_ptr, int));
					if (flags.meno)
						ft_putpad(npad[0] - 1, flags.pad);
				}
				else if (str[i + 1] == 's')
				{
					strvar = va_arg(arg_ptr, char *);
					if (flags.punto)
					{
						strvar = ft_substr(strvar, 0, npad[1]);
					}
					if (!flags.meno)
						ft_putpad(npad[0] - ft_strlen(strvar), ' ');
					ft_putstr(strvar);
					if (flags.meno)
						ft_putpad(npad[0] - ft_strlen(strvar), ' ');
				}
				else if (str[i + 1] == 'p')
				{
					n = (long)va_arg(arg_ptr, void*);
					if (!flags.meno)
					{
						ft_putpad(npad[0] - nbrlen(n, 16) - 2, flags.pad);
					}
					ft_putstr(ptrtostr(n));
					if (flags.meno)
						ft_putpad(npad[0] - nbrlen(n, 16) - 2, flags.pad);
				}
				else if (str[i + 1] == 'd' || str[i + 1] == 'i')
				{
					n = va_arg(arg_ptr, int);
					managenbr(n, 10, 0, npad, flags);
				}
				else if (str[i + 1] == 'u')
				{
					n = va_arg(arg_ptr, unsigned int);
					managenbr(n, 10, 0, npad, flags);
				}
				else if (str[i + 1] == 'x' || str[i + 1] == 'X')
				{
					n = va_arg(arg_ptr, int);
					managenbr((unsigned int)n, 16, str[i + 1] - 'x', npad, flags);
				}
				i += 2;
			}
		}
	}
	va_end(arg_ptr);
	return (1);
}

int	main(int argn, char* argv[])
{
	if (argn == 1)
		return (1);
	ft_printf(argv[1], 's', -15);
}
