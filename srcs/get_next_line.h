/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:47:35 by haaghaja          #+#    #+#             */
/*   Updated: 2025/02/20 14:29:10 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4200
# endif
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

// get_next_line.c
char	*get_next_line(int fd);

// get_next_line_utils.c
int		ft_get_line(char **str, char *buffer);
int		ft_strjoin(char *str1, char *str2);
char	*new_str(char *str, ssize_t bytes_read);
char	*exit_gnl(char *str, char *buffer);
void	shift_buffer(char *buffer);	
#endif
