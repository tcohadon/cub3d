/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmancho <lmancho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:22:51 by tcohadon          #+#    #+#             */
/*   Updated: 2025/06/13 15:28:50 by lmancho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_0(t_data *data, char *map_path)
{
	data->fd = -1;
	data->path = map_path;
	data->h = 0;
	data->w = 0;
}

int main(int ac, char **av)
{
	t_data data;
	(void)av;
	
	if (ac != 2)
		return (fd_printf(2, ERR_ARG), 1);
	init_0(&data, av[1]);
}