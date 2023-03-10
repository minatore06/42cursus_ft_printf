/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 14:52:33 by scaiazzo          #+#    #+#             */
/*   Updated: 2022/10/04 14:52:36 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int ch)
{
	if (ch < 65)
		return (0);
	if (ch > 122)
		return (0);
	if (ch < 97 && ch > 90)
		return (0);
	return (1);
}
