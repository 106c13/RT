/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:35:56 by haaghaja          #+#    #+#             */
/*   Updated: 2025/04/26 18:08:55 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_printf(char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		i += write(1, str, 1);
		str++;
	}
	return (i);
}

int	ft_htod(char **str)
{
	int	num;

	num = 0;
	(*str) += 3;
	while (**str && **str != ' ' && **str != '\n')
	{
		if (**str >= '0' && **str <= '9')
			num = num * 16 + **str - '0';
		else if (**str >= 'a' && **str <= 'f')
			num = num * 16 + **str - 'a' + 10;
		else if (**str >= 'A' && **str <= 'F')
			num = num * 16 + **str - 'A' + 10;
		(*str)++;
	}
	return (num);
}

int	get_color(int i)
{
	if (i == 2 || i == 3)
		return (0xff7000);
	if (i == 1)
		return (0xff0000);
	return (0xffffff);
}

int	gradient(int c1, int c2, float t)
{
	int	r;
	int	g;
	int	b;

	if (c1 == c2 || t == 0)
		return (c1);
	r = ((c1 >> 16) & 0xFF);
	r += (int)((((c2 >> 16) & 0xFF) - ((c1 >> 16) & 0xFF)) * t);
	g = ((c1 >> 8) & 0xFF);
	g += (int)((((c2 >> 8) & 0xFF) - ((c1 >> 8) & 0xFF)) * t);
	b = (c1 & 0xFF);
	b += (int)((((c2 & 0xFF) - (c1 & 0xFF)) * t));
	return ((r << 16) | (g << 8) | b);
}

void	reset_img(t_data *img)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
			my_mlx_pixel_put(img, x++, y, 0x222221);
		y++;
	}
}
