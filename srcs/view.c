/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:00:31 by haaghaja          #+#    #+#             */
/*   Updated: 2025/04/26 19:29:01 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_x(t_grid *grid, float angle)
{
	float	y;
	float	z;
	int		i;

	i = 0;
	while (i < grid->size)
	{
		y = grid->points[i].y;
		z = grid->points[i].z;
		grid->points[i].y = y * cos(angle) - z * sin(angle);
		grid->points[i].z = y * sin(angle) + z * cos(angle);
		i++;
	}
}

void	rotate_y(t_grid *grid, float angle)
{
	float	x;
	float	z;
	int		i;

	i = 0;
	while (i < grid->size)
	{
		x = grid->points[i].x;
		z = grid->points[i].z;
		grid->points[i].x = x * cos(angle) + z * sin(angle);
		grid->points[i].z = -x * sin(angle) + z * cos(angle);
		i++;
	}
}

void	rotate_z(t_grid *grid, float angle)
{
	float	x;
	float	y;
	int		i;

	i = 0;
	while (i < grid->size)
	{
		x = grid->points[i].x;
		y = grid->points[i].y;
		grid->points[i].x = x * cos(angle) - y * sin(angle);
		grid->points[i].y = x * sin(angle) + y * cos(angle);
		i++;
	}
}

void	project_perspective(t_point *p, float f, t_grid *grid)
{
	float	camera_z;
	float	relative_z;

	camera_z = 500.0f;
	relative_z = p->z - camera_z;
	if (relative_z > -1.0f)
		relative_z = -1.0f;
	p->x = (p->x * f) / relative_z + WIDTH / 2 + grid->x + 150;
	p->y = (p->y * f) / relative_z + HEIGHT / 2 + grid->y;
}

void	project_isometric(t_point *p, t_grid *grid)
{
	int	x;
	int	y;

	x = p->x - p->y + WIDTH / 2;
	y = (p->x + p->y) / 2 - p->z + HEIGHT / 2;
	p->x = x + grid->x + 150;
	p->y = y + grid->y;
}
