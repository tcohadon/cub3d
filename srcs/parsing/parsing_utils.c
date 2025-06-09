/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmancho <lmancho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 12:59:18 by lmancho           #+#    #+#             */
/*   Updated: 2025/06/09 17:52:13 by lmancho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	check_fd_error(t_data *data)
{
	if (data->map.fd < 0 || read(data->map.fd, 0, 0) < 0)
		exit (ft_printf("Error\nfd not working."));
}

void	allocate_and_initialize_copy_map(t_map *map)
{
	int	i;
	int	j;

	map->copy_map = (char **)malloc(sizeof(char *) * (map->h + 1));
	if (!map->copy_map)
		exit_with_error("Error\nFailed to allocate memory.");
	i = 0;
	while (i < map->h)
	{
		map->copy_map[i] = (char *)malloc(sizeof(char) * (map->w + 1));
		if (!map->copy_map[i])
			exit_with_error("Error\nFailed to allocate memory.");
		j = 0;
		while (j < map->w)
		{
			map->copy_map[i][j] = '0';
			j++;
		}
		map->copy_map[i][j] = '\0';
		i++;
	}
}

void	map_allocation(t_map *map)
{
	int	i;
	int	j;

	map->map = (char **)malloc(sizeof(char *) * (map->h + 1));
	if (!map->map)
		exit_with_error("Error\nFailed to allocate memory for grid.");
	i = 0;
	while (i < map->h)
	{
		map->map[i] = (char *)malloc(sizeof(char) * (map->w + 1));
		if (!map->map[i])
			exit_with_error("Error\nFailed to allocate memory for grid row.");
		j = 0;
		while (j < map->w)
		{
			map->map[i][j] = '0';
			j++;
		}
		map->map[i][j] = '\0';
		i++;
	}
}

void	finalgrid_allocation(t_map *map)
{
	map_allocation(map);
	allocate_and_initialize_copy_map(map);
}