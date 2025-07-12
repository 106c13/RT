/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:48:20 by haaghaja          #+#    #+#             */
/*   Updated: 2025/04/27 15:48:16 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	unselect_all(t_grid *grid)
{
	int	i;

	i = 0;
	while (i < grid->size)
	{
		grid->selected_points[i] = 0;
		i++;
	}
}

void	obj_reset(t_grid *grid)
{
	int	i;

	i = 0;
	grid->view_mode = 2;
	while (i < grid->size)
	{
		grid->points[i].x = grid->o_points[i].x;
		grid->points[i].y = grid->o_points[i].y;
		grid->points[i].z = grid->o_points[i].z;
		grid->points[i].color = grid->o_points[i].color;
		i++;
	}
}

t_point	create_point(t_grid *grid, int i, int edit_mode)
{
	t_point	p;

	p = grid->points[i];
	p.x *= grid->zoom;
	p.y *= grid->zoom;
	p.z *= grid->zoom;
	p.color = grid->points[i].color;
	if (edit_mode)
		p.color = get_color(grid->selected_points[i]);
	if (grid->view_mode == 1)
		project_perspective(&p, 600.0f, grid);
	else if (grid->view_mode == 2)
		project_isometric(&p, grid);
	return (p);
}

void	obj_init(t_grid *grid)
{
	int	i;
	int	width;
	int	height;
	int	scale;

	i = 0;
	width = grid->width;
	height = grid->height;
	scale = 5;
	while (i < grid->size)
	{
		grid->o_points[i].x = (i % width - width / 2) * scale;
		grid->o_points[i].y = (i / width - height / 2) * scale;
		grid->points[i].x = grid->o_points[i].x;
		grid->points[i].y = grid->o_points[i].y;
		if (grid->size < 1000)
			grid->o_points[i].z *= scale;
		grid->points[i].z = grid->o_points[i].z;
		grid->points[i].color = grid->o_points[i].color;
		i++;
	}
}
