/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:00:56 by haaghaja          #+#    #+#             */
/*   Updated: 2025/04/26 13:00:57 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	error(char *msg, int error_code)
{
	ft_printf(msg);
	return (error_code);
}

void	*error_ptr(char *msg, void *ptr)
{
	ft_printf(msg);
	return (ptr);
}
