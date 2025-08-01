/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_pos_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohadon <tcohadon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 01:25:44 by tcohadon          #+#    #+#             */
/*   Updated: 2025/08/01 19:47:35 by tcohadon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	init_player_pos(t_data *data, int x, int y, char angle)
{
	int	tile_px;
	int	tile_py;
	int	px;
	int	py;

	tile_px = x * T_SIZE;
	tile_py = y * T_SIZE;
	px = tile_px + (T_SIZE - PLAYER_SIZE) / 2;
	py = tile_py + (T_SIZE - PLAYER_SIZE) / 2;
	data->player->x = px + PLAYER_SIZE / 2;
	data->player->y = py + PLAYER_SIZE / 2;
	if (angle == 'N')
		data->player->angle = 270.0;
	else if (angle == 'S')
		data->player->angle = 90.0;
	else if (angle == 'W')
		data->player->angle = 180.0;
	else if (angle == 'E')
		data->player->angle = 0.0;
}

void	init_player(t_data *data)
{
	int	x;
	int	y;

	y = -1;
	while (data->copy_map[++y])
	{
		x = -1;
		while (data->copy_map[y][++x])
		{
			if (data->copy_map[y][x] == 'N' || data->copy_map[y][x] == 'S'
				|| data->copy_map[y][x] == 'E' || data->copy_map[y][x] == 'W')
				init_player_pos(data, x, y, data->copy_map[y][x]);
		}
	}
}
