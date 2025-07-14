#ifndef RT_H
# define RT_H
# define PI 3.14
# define WIDTH 600
# define HEIGHT 600
# define CIRCLE 0
# define HARD 1

# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include "../mlx/mlx.h"

typedef struct s_vec2
{
	float	x;
	float	y;
}	t_vec2;

typedef struct s_obj
{
	int	type;
	t_vec2	pos;
	int	color;
	float	r;
	int	count_points;
	float	*points_x;
	float	*points_y;
}	t_obj;

typedef struct s_cam
{
	t_vec2	pos;
	t_vec2	ornt;
}	t_cam;
typedef struct s_data
{
	void	*img;
	char	*addr;
	int		b;
	int		l;
	int		endian;
}	t_data;

typedef struct s_point
{
	float	x;
	float	y;
	int		color;
}	t_point;


typedef struct s_grid
{
	void	*mlx;
	void	*win;
	int		width;
	int		height;
	int		size;
	t_data	*img;
	t_cam	*cam;
	t_obj	*objs;
}	t_grid;


#endif
