/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:46:37 by haaghaja          #+#    #+#             */
/*   Updated: 2025/02/20 14:16:20 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*str;
	ssize_t		bytes_read;
	static char	buffer[BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = NULL;
	while (!ft_get_line(&str, buffer))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (exit_gnl(str, buffer));
		buffer[bytes_read] = '\0';
		if (bytes_read == 0)
			break ;
	}
	if (str == NULL || *str == '\0')
		return (exit_gnl(str, NULL));
	shift_buffer(buffer);
	return (str);
}
