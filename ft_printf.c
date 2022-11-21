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
#include "ft_printf.h"
#include "libft/libft.h"

#include <stdio.h>
#include <limits.h>
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

int	unnbrlen(unsigned long n, unsigned int base)
{
	int	ndig;

	ndig = 1;
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
void	managenbr(long n, int base, int uc, int uns, int *npad, t_flags flags)
{
	if (flags.numsign && base == 16 && n)
		npad[0] -= 2;
	if ((n < 0 || flags.piu || flags.spazio) && !uns)
		npad[0]--;
	if (!flags.meno)
		ft_putpad(npad[0] - max(npad[1], nbrlen(n, base)), (char)flags.pad);
	if (flags.numsign && base == 16 && n)
	{
		ft_putchar('0');
		if (uc)
			ft_putchar('X');
		else
			ft_putchar('x');
	}
	if (flags.piu && n >= 0 && !uns)
		ft_putchar('+');
	else if (flags.spazio && n >= 0 && !uns)
		ft_putchar(' ');
	ft_putpad(npad[1] - nbrlen(n, base), '0');
	if (uns)
		ft_putunnbrbase((unsigned long)n, base, uc);
	else
		ft_putnbrbase(n, base, uc);
	if (flags.meno)
		ft_putpad(npad[0] - max(npad[1], nbrlen(n, base)), ' ');
}

int	ptrtostr1(int *len[], int **npad, char** str, t_flags *flags)
{
	int	i;

	i = 0;
	if (flags->spazio || flags->piu)
	{
		(*len)[0]++;
		(*len)[1]++;
	}
	if (flags->punto || flags->meno)
		flags->pad = ' ';
	*str = malloc(sizeof(char) * ((*len)[0] + 1));
	if (flags->pad == ' ' && !flags->meno)
	{
		while (i < (*npad)[0] - (*len)[1] - max((*npad)[1], 12))
			(*str)[i++] = ' ';
	}
	if (flags->spazio)
		(*str)[i++] = ' ';
	if (flags->piu)
		(*str)[i++] = '+';
	(*str)[(*len)[0]] = 0;
	(*str)[i++] = '0';
	(*str)[i++] = 'x';
	return (i);
}

int	ptrtostr2(int *len, int *i, int *npad, char *str, t_flags flags)
{
	int	pre;

	if (flags.pad == '0')
	{
		while (*i < npad[0] + len[1] - max(npad[1], 12))
			str[(*i)++] = '0';
	}
	while (*i < npad[1] - 12 + len[1] + npad[0] - len[1] - max(npad[1], 12))
		str[(*i)++] = '0';
	pre = len[1] + max(max(npad[0] - (12 + len[1]), npad[1] - 12), 0);
	*i = len[0] - 1;
	if (flags.meno)
	{
		pre = len[1] + max(npad[1] - 12, 0);
		*i = len[0] - 1 - (npad[0] - 12 - pre);
	}
	return (pre);
}

char	*ptrtostr(long ptr, int i, int tmp, int *npad, t_flags flags)
{
	int		len[2];
	int		pre;
	char	*str;

	len[0] = 14 + max(npad[0] - 14, npad[1] - 12);
	len[1] = 2;
	i = ptrtostr1(&len, &npad, &str, &flags);
	pre = ptrtostr2(len, &i, npad, str, flags);
	while (i >= pre)
	{
		tmp = ptr % 16;
		if (tmp > 9)
			str[i] = tmp - 10 + 97;
		else
			str[i] = tmp + 48;
		ptr /= 16;
		i--;
	}
	if (flags.meno)
		i = len[0] - (npad[0] - len[1] - max(npad[1], 12));
	if (flags.meno)
		while (i < len[0])
			str[i++] = ' ';
	return (str);
}

int	get_flags(const char *str, char *set, t_flags *flags)
{
	int	i;

	i = 0;
	flags->pad = 32;
	flags->meno = 0;
	flags->punto = 0;
	flags->numsign = 0;
	flags->spazio = 0;
	flags->piu = 0;
	while (ft_strchr(set, *(str + i)))
	{
		if (*(str + i) == '-')
			flags->meno = 1;
		if (*(str + i) == '0' && !ft_isdigit(*(str + i - 1)) && !flags->meno)
			flags->pad = 48;
		if (*(str + i) == '.')
			flags->punto = 1;
		if (*(str + i) == '#')
			flags->numsign = 1;
		if (*(str + i) == '+')
			flags->piu = 1;
		if (*(str + i++) == ' ')
			flags->spazio = 1;
	}
	return (i);
}

int	manage_char_flag(int result, int *npad, t_flags flags, va_list arg_ptr)
{
	if (!flags.meno)
		ft_putpad(npad[0] - 1, flags.pad);
	result += max(1, npad[0]);
	ft_putchar((char)va_arg(arg_ptr, int));
	if (flags.meno)
		ft_putpad(npad[0] - 1, flags.pad);
	return (result);
}

int	manage_string_flag(int result, int *npad, t_flags flags, va_list arg_ptr)
{
	char	*strvar;

	strvar = va_arg(arg_ptr, char *);
	if (flags.punto)
		strvar = ft_substr(strvar, 0, npad[1]);
	result += max(npad[0], ft_strlen(strvar));
	if (!flags.meno)
		ft_putpad(npad[0] - ft_strlen(strvar), ' ');
	if (!strvar)
	{
		result += 6;
		ft_putstr("(null)");
	}
	else
		ft_putstr(strvar);
	if (flags.meno)
		ft_putpad(npad[0] - ft_strlen(strvar), ' ');
	if (flags.punto)
		free(strvar);
	return (result);
}

int	manage_ptr_flag(int result, int *npad, t_flags flags, va_list arg_ptr)
{
	long	n;
	char	*strvar;

	n = (long)va_arg(arg_ptr, void *);
	if (flags.spazio || flags.piu)
		result++;
	if (!n)
	{
		result += 5;
		ft_putstr("(nil)");
	}
	else if (nbrlen(n, 16) != 12)
	{
		result += unnbrlen((unsigned long)n, 16) + 2;
		if (flags.piu)
			ft_putchar('+');
		else if (flags.spazio)
			ft_putchar(' ');
		flags.numsign = 1;
		managenbr(n, 16, 0, 1, npad, flags);
	}
	else
	{
		result += max(npad[0], nbrlen(n, 16) + 2);
		strvar = ptrtostr(n, 0, 0, npad, flags);
		ft_putstr(strvar);
		free(strvar);
	}
	return (result);
}

int	manage_nbr_flag(int result, int *npad, t_flags flags, va_list arg_ptr)
{
	long	n;

	n = va_arg(arg_ptr, int);
	result += max(npad[0], max(npad[1], nbrlen(n, 10)));
	if ((flags.spazio || flags.piu) && n>=0)
		result++;
	managenbr(n, 10, 0, 0, npad, flags);
	return (result);
}

int	manage_uns_flag(int result, int *npad, t_flags flags, va_list arg_ptr)
{
	long	n;

	n = va_arg(arg_ptr, unsigned int);
	result += max(npad[0], max(npad[1], nbrlen(n, 10)));
	managenbr(n, 10, 0, 1, npad, flags);
	return (result);
}

int	manage_hex_flag(int result, int *npad, char flag, t_flags flags, va_list arg_ptr)
{
	long	n;

	n = va_arg(arg_ptr, unsigned int);
	result += max(npad[0], max(npad[1], unnbrlen(n, 16)));
	managenbr(n, 16, flag - 'x', 1, npad, flags);
	return (result);
}

int	manage_more_flags(int result, int *npad, char flag, t_flags flags, va_list arg_ptr)
{
	if (flag == 'c' || flag == 's' || flag == 'p'
		|| flag == 'd' || flag == 'i' || flag == 'u'
		|| flag == 'x' || flag == 'X')
	{
		if (flag == 'c')
			result = manage_char_flag(result, npad, flags, arg_ptr);
		else if (flag == 's')
			result = manage_string_flag(result, npad, flags, arg_ptr);
		else if (flag == 'p')
			result = manage_ptr_flag(result, npad, flags, arg_ptr);
		else if (flag == 'd' || flag == 'i')
			result = manage_nbr_flag(result, npad, flags, arg_ptr);
		else if (flag == 'u')
			result = manage_uns_flag(result, npad, flags, arg_ptr);
		else if (flag == 'x' || flag == 'X')
			result = manage_hex_flag(result, npad, flag, flags, arg_ptr);
	}
	return (result);
}
//HEY questa roba forse e' finita
int	manage_flags(int i, int **npad, char *str, t_flags *flags)
{
	i += get_flags(&str[i], "-0# +", flags);
	while (ft_isdigit(str[i]))
	{
		(*npad)[0] *= 10;
		(*npad)[0] += str[*i] - 48;
		i++;
	}
	if (str[i] == '.')
	{
		i++;
		while (ft_isdigit(str[*i]))
		{
			(*npad)[1] *= 10;
			(*npad)[1] += str[i] - 48;
			i++;
		}
		flags->punto = 1;
	}
	return (i);
}

void	reset(int *npad, t_flags *flags)
{
	(*npad)[0] = 0;
	(*npad)[1] = 0;
	flags->pad = 32;
	flags->meno = 0;
}

int	manage_almost_flag(int *i, int result)
{
	ft_putchar('%');
	(*i) += 2;
	return (++result);
}

int	manage_real_flags(int *i, int result, char *str, va_list arg_ptr)
{
	int		npad[2];
	t_flags	flags;

	reset(&npad, &flags);
	(*i)++
	*i = manage_flags(*i, &npad, str, &flags);
	result = manage_more_flags(result, npad, str[*i], flags, arg_ptr);
	(*i)++;
	return (result)
}

int	manage_no_flag(int *i, int result, char *str)
{
	ft_putchar(*((char *)str + *i));
	(*i)++;
	return (++result);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		result;
	va_list arg_ptr;

	result = 0;
	i = 0;
	va_start(arg_ptr, str);
	while (*(str + i))
	{
		if (str[i] == '%' && str[i + 1] == '%')
			result = manage_almost_flag(&i, result);
		else if (str[i] == '%')
			result = manage_real_flag(&i, result, str, arg_ptr)
		else
			result = manage_no_flag(&i, result, str);

	}
	va_end(arg_ptr);
	return (result);
}
//-2147483648

int	main(int argn, char* argv[])
{
	if (argn == 1)
		return (1);
	//printf(argv[1], -1);
	printf("\n");
	if(ft_printf(argv[1], "gk") == printf(argv[1], "gk"))
		printf("\nyoo!!!");
}
