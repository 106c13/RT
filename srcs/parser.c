/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 14:53:22 by haaghaja          #+#    #+#             */
/*   Updated: 2025/04/28 12:48:20 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_atoi(char **str)
{
	int	num;
	int	sign;

	num = 0;
	sign = get_sign(str);
	while (**str >= '0' && **str <= '9')
	{
		num = num * 10 + **str - 48;
		(*str)++;
	}
	return (num * sign);
}

void	parse_line(char *line, t_grid *grid, int *i)
{
	int	width;

	width = 0;
	while (*line && *line != '\n')
	{
		if (*line != ' ')
		{
			grid->o_points[*i].z = ft_atoi(&line);
			if (*line == ',')
				grid->o_points[*i].color = ft_htod(&line);
			else
				grid->o_points[*i].color = 16777215;
			grid->selected_points[*i] = 0;
			(*i)++;
			width++;
		}
		line++;
	}
	grid->width = width;
}

void	parse_file(int fd, t_grid *grid)
{
	char	*line;
	int		height;
	int		i;

	line = get_next_line(fd);
	height = 0;
	i = 0;
	while (line)
	{
		height++;
		parse_line(line, grid, &i);
		free(line);
		line = get_next_line(fd);
	}
	grid->height = height;
}

int	create_grid(char *fname, t_grid *grid)
{
	int		size;
	int		fd;

	fd = open(fname, O_RDONLY);
	if (fd == -1)
		return (error("File not exists\n", 0));
	size = get_grid_size(fd);
	close(fd);
	if (size < 1)
		return (error("File is not valid\n", 0));
	grid->points = (t_point *)malloc(sizeof(t_point) * size);
	grid->o_points = (t_point *)malloc(sizeof(t_point) * size);
	grid->selected_points = (int *)malloc(sizeof(int) * size);
	if (!grid->points || !grid->o_points || !grid->selected_points)
		return (error("Can't allocate memory\n", 0));
	fd = open(fname, O_RDONLY);
	parse_file(fd, grid);
	grid->size = size;
	grid->x = 0;
	grid->y = 0;
	grid->zoom = 5;
	grid->s_point = 0;
	grid->view_mode = 2;
	close(fd);
	return (1);
}
