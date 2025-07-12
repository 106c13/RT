/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:38:58 by haaghaja          #+#    #+#             */
/*   Updated: 2025/04/26 18:39:18 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotation_handler(int keycode, t_grid *grid, int edit_mode)
{
	if (keycode == 97)
		rotate_z(grid, -0.1);
	else if (keycode == 100)
		rotate_z(grid, 0.1);
	else if (keycode == 119 && !edit_mode)
		rotate_x(grid, -0.1);
	else if (keycode == 115 && !edit_mode)
		rotate_x(grid, 0.1);
	else if (keycode == 113 && !edit_mode)
		rotate_y(grid, -0.1);
	else if (keycode == 101 && !edit_mode)
		rotate_y(grid, 0.1);
}

void	grid_setting_handler(int keycode, t_grid *grid)
{
	if (keycode == 32)
		grid->zoom += 0.1;
	else if (keycode == 65289)
		grid->zoom -= 0.1;
	else if (keycode == 65363)
		grid->x += 8;
	else if (keycode == 65361)
		grid->x -= 8;
	else if (keycode == 65364)
		grid->y += 8;
	else if (keycode == 65362)
		grid->y -= 8;
	else if (keycode == 61)
		change_height(grid, 1);
	else if (keycode == 45)
		change_height(grid, -1);
	else if (keycode == 49)
		grid->view_mode = 1;
	else if (keycode == 50)
		grid->view_mode = 2;
}

void	editor_handler(int keycode, t_grid *grid)
{
	if (keycode == 99)
	{
		grid->selected_points[grid->s_point]++;
		grid->selected_points[grid->s_point] %= 2;
	}
	else if (keycode == 120)
		unselect_all(grid);
	else if (keycode == 107 && grid->s_point + grid->width < grid->size)
		grid->s_point += grid->width;
	else if (keycode == 105 && grid->s_point - grid->width >= 0)
		grid->s_point -= grid->width;
	else if (keycode == 106 && grid->s_point != 0)
		grid->s_point -= 1;
	else if (keycode == 108 && grid->s_point != grid->size - 1)
		grid->s_point += 1;
}

int	event_handler(int keycode, t_grid *grid)
{
	static int	edit_mode;

	if (keycode == 65307)
		fdf_exit(grid);
	else if (keycode == 118)
	{
		edit_mode++;
		if (edit_mode == 1)
			obj_reset(grid);
		else
			edit_mode = 0;
	}
	rotation_handler(keycode, grid, edit_mode);
	grid_setting_handler(keycode, grid);
	editor_handler(keycode, grid);
	if (grid->zoom < 0.1)
		grid->zoom = 0.1;
	draw_map(grid, edit_mode);
	draw_menu(grid);
	return (0);
}
