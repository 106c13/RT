/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 14:52:06 by haaghaja          #+#    #+#             */
/*   Updated: 2025/04/28 13:56:49 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	is_valid_symbol(char c, char *s)
{
	while (*s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}

int	is_color(char **str)
{
	int	i;

	i = 0;
	(*str)++;
	if (**str != '0' || *(*str + 1) != 'x')
		return (0);
	*str += 2;
	while (i < 6)
	{
		if (*(*str + i) == ' ' || *(*str + i) == '\n' || *(*str + i) == '\0')
			break ;
		if (!is_valid_symbol(*(*str + i), "0123456789ABCDEFabcdef"))
			return (0);
		i++;
	}
	if (i == 0)
		return (0);
	*str += i;
	if (**str != ' ' && **str != '\n' && **str != '\0')
		return (0);
	return (1);
}

int	is_valid(char **str)
{
	if (!is_int(str))
		return (0);
	if (**str == ',')
		return (is_color(str));
	return (1);
}

int	count_words(char *str)
{
	int	count;
	int	first;

	count = 0;
	first = 1;
	while (*str && *str != '\n')
	{
		if (*str != ' ' && (first || *(str - 1) == ' '))
		{
			if (!is_valid(&str))
				return (-1);
			count++;
		}
		first = 0;
		str++;
	}
	if (first == 1)
		return (-1);
	return (count);
}

int	get_grid_size(int fd)
{
	int		size;
	int		width;
	char	*line;

	size = 0;
	width = 0;
	line = get_next_line(fd);
	while (line)
	{
		width = count_words(line);
		if (width <= 0 || size % width != 0)
		{
			free(line);
			return (-1);
		}
		size += width;
		free(line);
		line = get_next_line(fd);
	}
	return (size);
}
