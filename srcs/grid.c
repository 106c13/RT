/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:41:05 by haaghaja          #+#    #+#             */
/*   Updated: 2025/04/29 14:17:06 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_abs(float c)
{
	if (c < 0)
		c *= -1;
	return ((int)c);
}

int	update_points(t_point *p0, t_point *p1, int a, char c)
{
	if (c == 'x')
	{
		if (p0->x < p1->x)
			p0->x++;
		else
			p0->x--;
	}
	else if (c == 'y')
	{
		if (p0->y < p1->y)
			p0->y++;
		else
			p0->y--;
	}
	return (a);
}

int	compute_outcode(t_point p)
{
	int	outcode;

	outcode = INSIDE;
	if (p.x < X_MIN)
		outcode |= LEFT;
	else if (p.x > X_MAX)
		outcode |= RIGHT;
	if (p.y < Y_MIN)
		outcode |= BOTTOM;
	else if (p.y > Y_MAX)
		outcode |= TOP;
	return (outcode);
}

void	cohen_sutherland_clip(t_point *p0, t_point *p1)
{
	int	outcode0;
	int	outcode1;
	int	outcodeOut;
	int	accept;
	int	x;
	int	y;

	outcode0 = compute_outcode(*p0);
	outcode1 = compute_outcode(*p1);
	accept = 0;
	x = 0;
	y = 0;
	while (1) {
		if ((outcode0 == INSIDE) && (outcode1 == INSIDE)) {
			accept = 1;
			break;
		}
		else if ((outcode0 & outcode1) != 0) {
			break;
		} else {
			outcodeOut = outcode0 ? outcode0 : outcode1;
			if (outcodeOut & TOP) {
				x = p0->x + (p1->x - p0->x) * (Y_MAX - p0->y) / (p1->y - p0->y);
				y = Y_MAX;
			} else if (outcodeOut & BOTTOM) {
				x = p0->x + (p1->x - p0->x) * (Y_MIN - p0->y) / (p1->y - p0->y);
				y = Y_MIN;
			} else if (outcodeOut & RIGHT) {
				y = p0->y + (p1->y - p0->y) * (X_MAX - p0->x) / (p1->x - p0->x);
				x = X_MAX;
			} else if (outcodeOut & LEFT) {
				y = p0->y + (p1->y - p0->y) * (X_MIN - p0->x) / (p1->x - p0->x);
				x = X_MIN;
			}
			if (outcodeOut == outcode0) {
				p0->x = x;
				p0->y = y;
				outcode0 = compute_outcode(*p0);
			} else {
				p1->x = x;
				p1->y = y;
				outcode1 = compute_outcode(*p1);
			}
		}
	}
	if (!accept)
		p0->x = p0->y = p1->x = p1->y = -1;
}

void	draw_line(t_point p0, t_point p1, t_data *img)
{
	int		dx;
	int		dy;
	int		err;
	float	i;
	float	n;

	cohen_sutherland_clip(&p0, &p1);
	if (p0.x == -1 || p0.y == -1 || p1.x == -1 || p1.y == -1)
		return;


	dx = ft_abs(p1.x - p0.x);
	dy = ft_abs(p1.y - p0.y);
	err = dx - dy;
	i = 0;
	n = dx;
	if (dx < dy)
		n = dy;
	if (dx == 0 && dy == 0)
		my_mlx_pixel_put(img, p0.x, p0.y, p0.color);
	while (ft_abs(p0.x - p1.x) > 0 || ft_abs(p0.y - p1.y) > 1)
	{
		my_mlx_pixel_put(img, p0.x, p0.y, gradient(p0.color, p1.color, i / n));
		if (err > -dy)
			err -= update_points(&p0, &p1, dy, 'x');
		if (err < dx)
			err += update_points(&p0, &p1, dx, 'y');
		i++;
	}
}

void	draw_map(t_grid *grid, int edit_mode)
{
	int		i;
	t_point	a;
	t_point	b;

	i = 0;
	reset_img(grid->img);
	grid->selected_points[grid->s_point] += 2;
	while (i < grid->size)
	{
		a = create_point(grid, i, edit_mode);
		if (i % grid->width < grid->width - 1)
		{
			b = create_point(grid, i + 1, edit_mode);
			draw_line(a, b, grid->img);
		}
		if (i / grid->width < grid->height - 1)
		{
			b = create_point(grid, i + grid->width, edit_mode);
			draw_line(a, b, grid->img);
		}
		i++;
	}
	mlx_put_image_to_window(grid->mlx, grid->win, grid->img->img, 0, 0);
	grid->selected_points[grid->s_point] -= 2;
}
