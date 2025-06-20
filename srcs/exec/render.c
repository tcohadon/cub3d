/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohadon <tcohadon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:48:00 by tcohadon          #+#    #+#             */
/*   Updated: 2025/06/20 13:07:29 by tcohadon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	render_player_minimap(t_data *data)
{
	int	px;
	int	py;

	px = (int)data->player->x - PLAYER_SIZE / 2;
	py = (int)data->player->y - PLAYER_SIZE / 2;
	data->texture->iplayer->instances[0].x = px;
	data->texture->iplayer->instances[0].y = py;

}

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
	mlx_image_to_window(data->mlx, data->texture->ifloor, tile_px, tile_py);
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

void	render_map(t_data *data)
{
	int			x;
	int			y;
	mlx_image_t	*image;

	y = -1;
	while (data->copy_map[++y])
	{
		x = -1;
		while (data->copy_map[y][++x])
		{
			image = NULL;
			if (data->copy_map[y][x] == '1')
				image = data->texture->iwall;
			else if (data->copy_map[y][x] == '0')
				image = data->texture->ifloor;
			else if (data->copy_map[y][x] == 'N' || data->copy_map[y][x] == 'S' ||
				data->copy_map[y][x] == 'E' || data->copy_map[y][x] == 'W')
				init_player_pos(data, x, y, data->copy_map[y][x]);
			if (image)
				mlx_image_to_window(data->mlx, image, x * T_SIZE, y * T_SIZE);
		}
	}
	render_player(data);
}

void	render_player(t_data *data)
{
	if (!data->player->x || !data->player->y)
		return ;
	mlx_image_to_window(data->mlx, data->texture->iplayer, data->player->x, data->player->y);
	data->player->x +=  PLAYER_SIZE / 2;
	data->player->y += PLAYER_SIZE / 2;
}