/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:09:59 by haaghaja          #+#    #+#             */
/*   Updated: 2025/04/26 14:42:05 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define COLOR_FRONT 0xFFFFFF
#define COLOR_SHADOW 0x555555
#define THICKNESS 5
#define OFFSET 5

void	draw_rect(t_data *img, t_rect r)
{
	int	i;
	int	j;

	i = 0;
	while (i < r.h)
	{
		j = 0;
		while (j < r.w)
		{
			my_mlx_pixel_put(img, r.x + j, r.y + i, r.color);
			j++;
		}
		i++;
	}
}

void	draw_f(t_data *img, int x, int y, int color)
{
	t_rect	r;

	r = (t_rect){x, y, THICKNESS, 100, color};
	draw_rect(img, r);
	r = (t_rect){x, y, 50, THICKNESS, color};
	draw_rect(img, r);
	r = (t_rect){x, y + 40, 35, THICKNESS, color};
	draw_rect(img, r);
}

void	draw_d(t_data *img, int x, int y, int color)
{
	t_rect	r;

	r = (t_rect){x, y, THICKNESS, 100, color};
	draw_rect(img, r);
	r = (t_rect){x, y, 40, THICKNESS, color};
	draw_rect(img, r);
	r = (t_rect){x, y + 100 - THICKNESS, 40, THICKNESS, color};
	draw_rect(img, r);
	r = (t_rect){x + 40, y + THICKNESS, THICKNESS, 100 - 2 * THICKNESS, color};
	draw_rect(img, r);
}

void	draw_fdf(t_data *img)
{
	int	start_x;
	int	start_y;

	start_x = 40;
	start_y = 40;
	draw_f(img, start_x + OFFSET, start_y + OFFSET, COLOR_SHADOW);
	draw_d(img, start_x + 70 + OFFSET, start_y + OFFSET, COLOR_SHADOW);
	draw_f(img, start_x + 140 + OFFSET, start_y + OFFSET, COLOR_SHADOW);
	draw_f(img, start_x, start_y, COLOR_FRONT);
	draw_d(img, start_x + 70, start_y, COLOR_FRONT);
	draw_f(img, start_x + 140, start_y, COLOR_FRONT);
}
