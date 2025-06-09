/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmancho <lmancho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:22:51 by tcohadon          #+#    #+#             */
/*   Updated: 2025/06/09 17:52:39 by lmancho          ###   ########.fr       */
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

void	prepare_flood()
{
	while(!map[i][j])
	{
		if (map[i][j] == '1')
			return ;
		else if (map[i][j] == '0')
			flood_fill(map[i][j]);		
	}
}

int	flood_fill(char **map, int i, int j)
{
	if (map[i][j] == '1')
		return (1);
	else if (map[i][j] == '0')
		map[i][j] = '2';
	else if (map[i][j] == ' ')
		return (fd_printf(2, ERR_MAP), 0);
	flood_fill(map, i + 1, j);
	flood_fill(map, i - 1, j);
	flood_fill(map, i, j + 1);
	flood_fill(map, i, j - 1);
}

int main(int ac, char **av)
{
	t_data data;
	(void)av;
	
	if (ac != 2)
		return (fd_printf(2, ERR_ARG), 1);
	init_0(data->map, av[1]);
}