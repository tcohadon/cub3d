/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmancho <lmancho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 12:59:18 by lmancho           #+#    #+#             */
/*   Updated: 2025/07/23 11:39:19 by lmancho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static bool	allocate_and_initialize_copy_map(t_data *map)
{
	int	i;
	int	j;

	map->copy_map = (char **)malloc(sizeof(char *) * (map->h + 1));
	if (!map->copy_map)
		return (fd_printf(2, ERR_ALLOC, 1), false);
	i = 0;
	while (i < map->h)
	{
		map->copy_map[i] = (char *)malloc(sizeof(char) * (map->w + 1));
		if (!map->copy_map[i])
			return (fd_printf(2, ERR_ALLOC, 1), false);
		j = 0;
		while (j < map->w)
		{
			map->copy_map[i][j] = '0';
			j++;
		}
		map->copy_map[i][j] = '\0';
		i++;
	}
	map->copy_map[i] = NULL;
	return (true);
}

static bool	map_allocation(t_data *map)
{
	int	i;
	int	j;

	map->map = (char **)malloc(sizeof(char *) * (map->h + 1));
	if (!map->map)
		return (fd_printf(2, ERR_ALLOC, 1), false);
	i = 0;
	while (i < map->h)
	{
		map->map[i] = (char *)malloc(sizeof(char) * (map->w + 1));
		if (!map->map[i])
			return (fd_printf(2, ERR_ALLOC, 1), false);
		j = 0;
		while (j < map->w)
			j++;
		map->map[i][j] = '\0';
		i++;
	}
	map->map[i] = NULL;
	return (true);
}

bool	finalmap_allocation(t_data *map)
{
	if (!map_allocation(map))
	{
		free_all(map);
		return (false);
	}
	if (!allocate_and_initialize_copy_map(map))
	{
		free_all(map);
		return (false);
	}
	return (true);
}

bool	check_space_map(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == '0' || data->map[y][x] == 'S'
				|| data->map[y][x] == 'E' || data->map[y][x] == 'N'
				|| data->map[y][x] == 'W')
			{
				if (y == 0 || y == data->h - 1 || x == 0 || x == data-> w - 1
					|| data->map[y - 1][x] == ' ' || data->map[y + 1][x] == ' '
					|| data->map[y][x - 1] == ' ' || data->map[y][x + 1] == ' ')
				{
					return (fd_printf(2, ERR_SPACE), false);
				}
			}
			x++;
		}
		y++;
	}
	return (true);
}
