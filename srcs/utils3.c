/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:41:18 by haaghaja          #+#    #+#             */
/*   Updated: 2025/04/28 14:00:34 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_sign(char **str)
{
	if (**str == '-')
	{
		(*str)++;
		return (-1);
	}
	return (1);
}

int	trim_zeros(char **str)
{
	while (**str == '0')
		(*str)++;
	if (is_valid_symbol(**str, "0123456789"))
		return (0);
	return (1);
}

int	is_int(char **str)
{
	long	num;
	int		sign;
	int		lenght;

	sign = get_sign(str);
	lenght = trim_zeros(str);
	num = 0;
	while (**str && **str != ',' && **str != '\n' && **str != ' ')
	{
		if (!is_valid_symbol(**str, "0123456789"))
			return (0);
		num = num * 10 + (**str - '0');
		(*str)++;
		lenght++;
	}
	if (lenght == 0 || lenght > 10)
		return (0);
	if (sign * num > INT_MAX || sign * num < INT_MIN)
		return (0);
	return (1);
}
