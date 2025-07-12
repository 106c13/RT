#ifndef FDF_H
# define FDF_H

# define PI 3.14
# define WIDTH 600
# define HEIGHT 600

# define X_MIN 0
# define Y_MIN 0
# define X_MAX WIDTH
# define Y_MAX HEIGHT

# define INSIDE 0
# define LEFT   1
# define RIGHT  2
# define BOTTOM 4
# define TOP    8

# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include "../mlx/mlx.h"

typedef struct s_vec3
{
	float	x;
	float	y;
}	t_vec3;

typedef struct s_obj
{
	t_vec3	pos;
	int	color;
	float	r;
}	t_obj;

typedef struct s_cam
{
	t_vec3	pos;
	t_vec3	ornt;
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
