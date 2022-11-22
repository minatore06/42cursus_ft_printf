/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_manage_flags1.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:42:32 by scaiazzo          #+#    #+#             */
/*   Updated: 2022/11/22 11:42:36 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	manage_char_flag(int result, t_flags flags, va_list arg_ptr)
{
	if (!flags.meno)
		ft_putpad(flags.npad[0] - 1, flags.pad);
	result += max(1, flags.npad[0]);
	ft_putchar((char)va_arg(arg_ptr, int));
	if (flags.meno)
		ft_putpad(flags.npad[0] - 1, flags.pad);
	return (result);
}

int	manage_string_flag(int result, t_flags flags, va_list arg_ptr)
{
	char	*strvar;

	strvar = va_arg(arg_ptr, char *);
	if (flags.punto)
		strvar = ft_substr(strvar, 0, flags.npad[1]);
	result += max(flags.npad[0], ft_strlen(strvar));
	if (!flags.meno)
		ft_putpad(flags.npad[0] - ft_strlen(strvar), ' ');
	if (!strvar)
	{
		result += 6;
		ft_putstr("(null)");
	}
	else
		ft_putstr(strvar);
	if (flags.meno)
		ft_putpad(flags.npad[0] - ft_strlen(strvar), ' ');
	if (flags.punto)
		free(strvar);
	return (result);
}

int	manage_nbr_flag(int result, t_flags flags, va_list arg_ptr)
{
	long	n;

	n = va_arg(arg_ptr, int);
	result += max(flags.npad[0], max(flags.npad[1], nbrlen(n, 10, 0)));
	if ((flags.spazio || flags.piu) && n >= 0)
		result++;
	managenbr(n, 10, 0, flags);
	return (result);
}

int	manage_uns_flag(int result, t_flags flags, va_list arg_ptr)
{
	long	n;

	n = va_arg(arg_ptr, unsigned int);
	result += max(flags.npad[0], max(flags.npad[1], nbrlen(n, 10, 0)));
	managenbr(n, 10, 1, flags);
	return (result);
}

int	manage_hex_flag(int result, char flag, t_flags flags, va_list arg_ptr)
{
	int		uc;
	long	n;

	uc = 'x' - flag;
	n = va_arg(arg_ptr, unsigned int);
	result += max(flags.npad[0], max(flags.npad[1], unnbrlen(n, 16)));
	managenbr(n, 16, uc + 1, flags);
	return (result);
}
