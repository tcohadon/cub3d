/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmancho <lmancho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 12:59:18 by lmancho           #+#    #+#             */
/*   Updated: 2025/06/23 15:01:55 by lmancho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	allocate_and_initialize_copy_map(t_data *map)
{
	int	i;
	int	j;

	map->copy_map = (char **)malloc(sizeof(char *) * (map->h + 1));
	if (!map->copy_map)
		exit (fd_printf(2, "Error\nFailed to allocate memory."));
	i = 0;
	while (i < map->h)
	{
		map->copy_map[i] = (char *)malloc(sizeof(char) * (map->w + 1));
		if (!map->copy_map[i])
			exit (fd_printf(2,"Error\nFailed to allocate memory."));
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
}

static void	map_allocation(t_data *map)
{
	int	i;
	int	j;

	map->map = (char **)malloc(sizeof(char *) * (map->h + 1));
	if (!map->map)
		exit (fd_printf(2, "Error\nFailed to allocate memory."));
	i = 0;
	while (i < map->h)
	{
		map->map[i] = (char *)malloc(sizeof(char) * (map->w + 1));
		if (!map->map[i])
			exit (fd_printf(2, "Error\nFailed to allocate memory."));
		j = 0;
		while (j < map->w)
		{
			//map->map[i][j] = '';
			j++;
		}
		map->map[i][j] = '\0';
		i++;
	}
	map->map[i] = NULL;
}

void	finalmap_allocation(t_data *map)
{
	map_allocation(map);
	allocate_and_initialize_copy_map(map);
}