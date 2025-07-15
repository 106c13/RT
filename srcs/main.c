/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:12:16 by haaghaja          #+#    #+#             */
/*   Updated: 2025/04/26 18:39:31 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "rt.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	dst = data->addr + (y * data->l + x * (data->b / 8));
	*(int *)dst = color;
}

int	fdf_exit(void *param)
{
	t_grid	*grid;

	grid = (t_grid *)param;
	mlx_destroy_image(grid->mlx, grid->img->img);
	mlx_destroy_window(grid->mlx, grid->win);
	mlx_destroy_display(grid->mlx);
	free(grid->mlx);
	exit(0);
	return (1);
}

void	reset(t_data *img)
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			my_mlx_pixel_put(img, j, i, 0x000000);
		}
	}
}

void	draw_cam(t_data *img, t_cam *cam)
{
	float	x;
	float	y;
	float	dx;
	float	dy;
	float	ox;
	float	oy;

	ox = cam->ornt.x;
	oy = cam->ornt.y;
	/*
	for (float t = 0.0; t < 50; t += 0.1)
	{
		x = cam->pos.x + t * ox;
		y = cam->pos.y + t * oy;
		my_mlx_pixel_put(img, x, y, 0xFFFFFF);
	}*/
	dx = ox * cos(PI*0.25) - oy * sin(PI*0.25);
	dy = ox * sin(PI*0.25) + oy * cos(PI*0.25);
	for (float t = 0.0; t < 50; t += 0.1)
	{
		x = cam->pos.x + t * dx;
		y = cam->pos.y + t * dy;
		my_mlx_pixel_put(img, x, y, 0xFFFFFF);
	}
	dx = ox * cos(PI*(-0.25)) - oy * sin(PI*(-0.25));
	dy = ox * sin(PI*(-0.25)) + oy * cos(PI*(-0.25));
	for (float t = 0.0; t < 50; t += 0.1)
	{
		x = cam->pos.x + t * dx;
		y = cam->pos.y + t * dy;
		my_mlx_pixel_put(img, x, y, 0xFFFFFF);
	}
}


/* Draw circle
y^2 - 2*y*s->y + s->y^2 + (x - s->x)^2 - s->r^2
D = 
*/
void	draw_s(t_data *img, t_obj *s)
{
	float	x;
	float	y;
	float	d;

	x = s->pos.x - s->r;
	for (float i = 0; i < 2*s->r; i += 0.1)
	{
		d = pow(2*s->pos.y, 2) - 4 * (pow(x - s->pos.x, 2) - pow(s->r,2) + pow(s->pos.y,2));
		if (d < 0)
			continue;
		d = sqrt(d);
		y = (2*s->pos.y - d)/2;
		my_mlx_pixel_put(img, x, y, 0x939ca7);
		y = (2*s->pos.y + d)/2;
		my_mlx_pixel_put(img, x, y, 0x939ca7);
		x += 0.1;
	}
}

/*
A = (x1, y1)
B = (x2, y2)
C = (x3, y3)
d = (x2 - x1) (y2 - y1)
P(t) = A + t*d; t>=0
Q(t) = B + u*(C - B); u E[0,1]
*/

int find_hit_hard(t_obj *s, t_cam *cam, float *x, float *y)
{
	float	x1, x2, x3;
	float	y1, y2, y3;
	float	dx, dy;
	float	dist, d = 10000;
	float	px, py;
	float	ox, oy;
	float	denom;
	float	t, u;
	int	i;

	x1 = cam->pos.x;
	y1 = cam->pos.y;
	dx = cam->ornt.x;
	dy = cam->ornt.y;
	i = -1;
	while (i++ < s->count_points)
	{
		if (i == s->count_points - 1)
		{
			x2 = s->points_x[i];
			x3 = s->points_x[0];
			y2 = s->points_y[i];
			y3 = s->points_y[0];
		}
		else
		{
			x2 = s->points_x[i];
			x3 = s->points_x[i + 1];
			y2 = s->points_y[i];
			y3 = s->points_y[i + 1];
		}
		px = x3 - x2;
		py = y3 - y2;
		ox = x2 - x1;
		oy = y2 - y1;
		denom = (dx*py - dy*px);
		if (denom == 0)
			continue ;
		t = (ox*py - oy*px)/denom;
		u = (ox*dy - oy*dx)/denom;
		if (!(t >= 0 && u >= 0 && u <= 1))
			continue ;
		dist = sqrt(t*t*(dx*dx + dy*dy));
		if (dist < d)
		{
			d = dist;
			*x = x1 + t*dx;
			*y = y1 + t*dy;
		}
	}
	return (1);
}
int	find_hit(t_obj *s, t_cam *cam, float *x, float *y)
{
	if (s->type == HARD)
		return (find_hit_hard(s, cam, x, y));
	float dx, dy, fx, fy;
	float A, B, C;
	float D;
	float t;
	float x1 = cam->pos.x;
	float y1 = cam->pos.y;
	float x2 = x1 + cam->ornt.x;
	float y2 = y1 + cam->ornt.y;
	float x3 = s->pos.x;
	float y3 = s->pos.y;
	float R = s->r;

	dx = x2 - x1;
	dy = y2 - y1;
	fx = x1 - x3;
	fy = y1 - y3;
	A = dx*dx + dy*dy;
	B = 2 * (fx*dx + fy*dy);
	C = fx*fx + fy*fy - R*R;
	D = B*B - 4*A*C;
	if (D < 0)
		return (0);
	D = sqrt(D);
	t = (-B - D) / (2*A);
	if (t < 0)
		t = (-B + D) / (2*A);
	if (t < 0)
		return (0);
	*x = x1 + t * dx;
	*y = y1 + t * dy;
	return (1);
}

void	rotate(t_vec2 *p, float angle)
{
	float	x;
	float	y;

	x = p->x * cos(angle) - p->y * sin(angle);
	y = p->y * cos(angle) + p->x * sin(angle);
	p->x = x;
	p->y = y;
}

void	draw(t_grid *grid)
{
	float	x;
	float	y;
	int	i;
	t_cam	ray;

	reset(grid->img);
	draw_cam(grid->img, grid->cam);
	//draw_s(grid->img, &grid->objs[0]);
	for (float a = 0; a < 0.25; a += 0.01)
	{
		i = 0;
		while (i < 4)
		{
			ray = *grid->cam;
			rotate(&ray.ornt, PI*a);
			if (find_hit(&grid->objs[i], &ray, &x, &y))
				my_mlx_pixel_put(grid->img, x, y, grid->objs[i].color);
			ray = *grid->cam;
			rotate(&ray.ornt, PI*(-a));	
			if (find_hit(&grid->objs[i], &ray, &x, &y))
				my_mlx_pixel_put(grid->img, x, y, grid->objs[i].color);
			i++;
		}
	}
	mlx_put_image_to_window(grid->mlx, grid->win, grid->img->img, 0, 0);
}


int	event_handler(int keycode, t_grid *grid)
{
	static int	edit_mode;

	printf("KEycode: %d\n", keycode);
	if (keycode == 65307)
		fdf_exit(grid);
	else if (keycode == 115)
		grid->cam->pos.y += 4;
	else if (keycode == 119)
		grid->cam->pos.y -= 4;
	else if (keycode == 100)
		grid->cam->pos.x += 4;
	else if (keycode == 97)
		grid->cam->pos.x -= 4;
	else if (keycode == 65363)
		rotate(&grid->cam->ornt, PI*0.05);
	else if (keycode == 65361)
		rotate(&grid->cam->ornt, PI*(-0.05));
	draw(grid);
	return (0);
}
int	main()
{
	t_grid	grid;
	t_data	img;
	t_cam	cam;
	t_obj	s1;
	t_obj	s2;
	t_obj	s3;
	t_obj 	s4;

	grid.mlx = mlx_init();
	grid.win = mlx_new_window(grid.mlx, WIDTH, HEIGHT, "FDF");
	img.img = mlx_new_image(grid.mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.b, &img.l, &img.endian);
	grid.img = &img;

	/* ====== INIT SCENE =========== */
	cam.pos.x = WIDTH/2;
	cam.pos.y = HEIGHT/2;
	cam.ornt.x = 0.3;
	cam.ornt.y = 0.4;
	s1.type = CIRCLE;
	s1.pos.x = 200.0;
	s1.pos.y = 400.0;
	s1.r = 60;
	s1.color = 0xFF0000;
	s2.type = CIRCLE;
	s2.pos.x = 400.0;
	s2.pos.y = 300.0;
	s2.r = 40;
	s2.color = 0xFF00FF;
	s3.type = CIRCLE;
	s3.pos.x = 300.0;
	s3.pos.y = 390.0;
	s3.r = 100;
	s3.color = 0xeeb804;
	s4.type = HARD;
	s4.color = 0x0f61bc;
	s4.count_points = 5;
	s4.points_x = malloc(sizeof(float) * 5);
	s4.points_y = malloc(sizeof(float) * 5);
	s4.points_x[0] = 100;
	s4.points_y[0] = 100;
	s4.points_x[1] = 200;
	s4.points_y[1] = 140;
	s4.points_x[2] = 260;
	s4.points_y[2] = 140;
	s4.points_x[3] = 200;
	s4.points_y[3] = 200;
	s4.points_x[4] = 130;
	s4.points_y[4] = 350;
	grid.cam = &cam;
	grid.objs = malloc(sizeof(t_obj) * 4);
	grid.objs[0] = s1;
	grid.objs[1] = s2;
	grid.objs[2] = s3;
	grid.objs[3] = s4;
	/* ============================= */
	draw(&grid);
	mlx_hook(grid.win, 2, 1L << 0, event_handler, &grid);
	mlx_hook(grid.win, 17, 0, fdf_exit, &grid);
	mlx_loop(grid.mlx);
	return (0);
}
