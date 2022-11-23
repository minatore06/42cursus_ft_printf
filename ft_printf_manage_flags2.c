/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_manage_flags2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:42:41 by scaiazzo          #+#    #+#             */
/*   Updated: 2022/11/22 11:42:44 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	manage_imptr_flag(int result, long n, t_flags flags)
{
	int	tmp;

	tmp = ft_max(flags.npad[1], unnbrlen((unsigned long)n, 16) + 2);
	result += ft_max(flags.npad[0], tmp);
	if (flags.piu)
		ft_putchar('+');
	else if (flags.spazio)
		ft_putchar(' ');
	flags.numsign = 1;
	managenbr(n, 16, 1, flags);
	return (result);
}

int	manage_ptr_flag(int result, t_flags flags, va_list arg_ptr)
{
	long	n;
	char	*strvar;

	n = (long)va_arg(arg_ptr, void *);
	if (flags.spazio || flags.piu)
		result++;
	if (!n)
	{
		if (!flags.meno)
			ft_putpad(flags.npad[0] - 5, ' ');
		result += 5 + ft_max(0, flags.npad[0] - 5);
		ft_putstr("(nil)", 1);
		if (flags.meno)
			ft_putpad(flags.npad[0] - 5, ' ');
	}
	else if (nbrlen(n, 16, 0) != 12)
		result = manage_imptr_flag(result, n, flags);
	else
	{
		result += ft_max(flags.npad[0], nbrlen(n, 16, 0) + 2);
		strvar = ptrtostr(n, 0, 0, flags);
		ft_putstr(strvar, 1);
		free(strvar);
	}
	return (result);
}

int	manage_more_flags(int result, char flag, t_flags flags, va_list ap)
{
	char	*strvar;

	strvar = "";
	if (flag == 'c' || flag == 's' || flag == 'p'
		|| flag == 'd' || flag == 'i' || flag == 'u'
		|| flag == 'x' || flag == 'X')
	{
		if (flag == 'c')
			result = manage_char_flag(result, flags, ap);
		else if (flag == 's')
		{
			strvar = va_arg(ap, char *);
			result = manage_string_flag(result, strvar, flags);
		}
		else if (flag == 'p')
			result = manage_ptr_flag(result, flags, ap);
		else if (flag == 'd' || flag == 'i')
			result = manage_nbr_flag(result, flags, ap);
		else if (flag == 'u')
			result = manage_uns_flag(result, flags, ap);
		else if (flag == 'x' || flag == 'X')
			result = manage_hex_flag(result, flag, flags, ap);
	}
	return (result);
}

int	manage_flags(int i, const char *str, t_flags *flags)
{
	i += get_flags(&str[i], "-0# +", flags);
	while (ft_isdigit(str[i]))
	{
		flags->npad[0] *= 10;
		flags->npad[0] += str[i] - 48;
		i++;
	}
	if (str[i] == '.')
	{
		i++;
		while (ft_isdigit(str[i]))
		{
			flags->npad[1] *= 10;
			flags->npad[1] += str[i] - 48;
			i++;
		}
		flags->punto = 1;
	}
	if (flags->punto)
		flags->pad = 32;
	return (i);
}
