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
#include "fdf.h"

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

	for (float t = 0.0; t < 10; t += 0.1)
	{
		x = cam->pos.x - t * cam->ornt.x;
		y = cam->pos.y - t * cam->ornt.y;
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
		my_mlx_pixel_put(img, x, y, s->color);
		y = (2*s->pos.y + d)/2;
		my_mlx_pixel_put(img, x, y, s->color);
		x += 0.1;
	}
}

void	draw(t_grid *grid)
{
	reset(grid->img);
	draw_cam(grid->img, grid->cam);
	draw_s(grid->img, &grid->objs[0]);
	mlx_put_image_to_window(grid->mlx, grid->win, grid->img->img, 0, 0);
}


int	event_handler(int keycode, t_grid *grid)
{
	static int	edit_mode;

	printf("KEycode: %d\n", keycode);
	if (keycode == 65307)
		fdf_exit(grid);
	else if (keycode == 119)
		grid->cam->pos.y++;
	else if (keycode == 115)
		grid->cam->pos.y--;
	else if (keycode == 100)
		grid->cam->pos.x++;
	else if (keycode == 97)
		grid->cam->pos.x--;
	else if (keycode == 65361)
		grid->cam->ornt.y++;
	else if (keycode == 65363)
		grid->cam->pos.y--;
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

	grid.mlx = mlx_init();
	grid.win = mlx_new_window(grid.mlx, WIDTH, HEIGHT, "FDF");
	img.img = mlx_new_image(grid.mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.b, &img.l, &img.endian);
	grid.img = &img;

	/* ====== INIT SCENE =========== */
	cam.pos.x = WIDTH/2;
	cam.pos.y = HEIGHT/2;
	cam.ornt.x = 10.0;
	cam.ornt.y = 10.0;
	s1.pos.x = 50.0;
	s1.pos.y = 50.0;
	s1.r = 30;
	s1.color = 0xFF0000;
	s2.pos.x = 20.0;
	s2.pos.y = 20.0;
	s2.r = 10;
	s2.color = 0xFF00FF;
	grid.cam = &cam;
	grid.objs = malloc(sizeof(t_obj) * 2);
	grid.objs[0] = s1;
	grid.objs[1] = s2;
	/* ============================= */
	draw(&grid);
	mlx_hook(grid.win, 2, 1L << 0, event_handler, &grid);
	mlx_hook(grid.win, 17, 0, fdf_exit, &grid);
	mlx_loop(grid.mlx);
	return (0);
}
