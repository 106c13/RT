/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:00:22 by haaghaja          #+#    #+#             */
/*   Updated: 2025/04/26 14:43:13 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->l + x * (data->b / 8));
	*(int *)dst = color;
}

void	draw_background(t_data *img)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH / 17 * 3)
		{
			my_mlx_pixel_put(img, x, y, 0x37383b);
			x++;
		}
		y++;
	}
}

void	put_text(t_grid *grid, int y, int color, char *str)
{
	mlx_string_put(grid->mlx, grid->win, 40, y, color, str);
}

void	draw_menu(t_grid *grid)
{
	draw_background(grid->img);
	draw_fdf(grid->img);
	put_text(grid, 200, 0xFFFFFF, "Menu");
	put_text(grid, 240, 0xe5e5df, "X: Left/Right");
	put_text(grid, 260, 0xe5e5df, "Y: Up/Down");
	put_text(grid, 320, 0xe5e5df, "X angle: W S");
	put_text(grid, 340, 0xe5e5df, "Y angle: Q E");
	put_text(grid, 360, 0xe5e5df, "Z angle: A D");
	put_text(grid, 400, 0xe5e5df, "Zoom in/out: Space/Tab");
	put_text(grid, 440, 0xe5e5df, "Perspective: 1");
	put_text(grid, 460, 0xe5e5df, "Isometric: 2");
	put_text(grid, 520, 0xe5e5df, "Editor Mode");
	put_text(grid, 540, 0xe5e5df, "Enter/Exit: V");
	put_text(grid, 560, 0xe5e5df, "Select point: C");
	put_text(grid, 580, 0xe5e5df, "Deselect point: C");
	put_text(grid, 600, 0xe5e5df, "Deselect all: X");
	put_text(grid, 620, 0xe5e5df, "Increase height: +");
	put_text(grid, 640, 0xe5e5df, "Decrease height: -");
	put_text(grid, 690, 0xe5e5df, "Move Left: J");
	put_text(grid, 710, 0xe5e5df, "Move Right: L");
	put_text(grid, 730, 0xe5e5df, "Move Up: I");
	put_text(grid, 750, 0xe5e5df, "Move Down: K");
}

void	change_height(t_grid *grid, int value)
{
	int	i;

	i = 0;
	while (i < grid->size)
	{
		if (grid->selected_points[i] != 0)
		{
			grid->o_points[i].z += value;
			grid->points[i].z += value;
		}
		i++;
	}
}
