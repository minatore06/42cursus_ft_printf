/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 18:12:35 by scaiazzo          #+#    #+#             */
/*   Updated: 2022/10/14 18:12:37 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

typedef struct s_flags{
	int	pad;
	int	meno;
	int	punto;
	int	numsign;
	int	spazio;
	int	piu;
}	t_flags;

#endif
