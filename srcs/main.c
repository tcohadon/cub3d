/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmancho <lmancho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:22:51 by tcohadon          #+#    #+#             */
/*   Updated: 2025/06/09 15:22:28 by lmancho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_0(t_map *map, char *map_path)
{
	map->fd = -1;
	map->path = map_path;
	map->h = 0;
	map->w = 0;
}

int main(int ac, char **av)
{
	t_data data;
	(void)av;
	
	if (ac != 2)
		return (fd_printf(2, ERR_ARG), 1);
	init_0(data.map, av[1]);
}