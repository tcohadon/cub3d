/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cohadontom <cohadontom@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:59:04 by cohadontom        #+#    #+#             */
/*   Updated: 2025/07/13 12:34:26 by cohadontom       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Remplacer TOUT le contenu de minimap.c par ceci :

#include "../../include/cub3d.h"

void init_minimap(t_data *data)
{
	int map_w = data->w * MINIMAP_TILE;
	int map_h = data->h * MINIMAP_TILE;
	int	y;
	int	x;
	uint32_t	col;
	uint32_t	*px;
	int			i;
	int	xx;
	int	yy;
	y = -1;
	data->texture->imini_player = NULL;
	data->texture->iminimap_bg = NULL;
	data->texture->iminimap_bg = mlx_new_image(data->mlx, map_w, map_h);
	uint32_t *bg = (uint32_t *)data->texture->iminimap_bg->pixels;
	while (++y < data->h)
	{
		x = -1;
		while (++x < data->w)
		{
			if (data->map[y][x] == '1')
				col = 0xFFFFFFFF;
			else
				col = 0xFFAAAAAA;
			yy = -1;
			while (++yy < MINIMAP_TILE)
			{
				xx = -1;
				while (++xx < MINIMAP_TILE)
					bg[(y * MINIMAP_TILE + yy) * map_w + (x * MINIMAP_TILE + xx)] = col;
			}
		}
	}
	mlx_image_to_window(data->mlx, data->texture->iminimap_bg,
				data->mini_offset_x, data->mini_offset_y);
	data->texture->imini_player = mlx_new_image(data->mlx,
		MINIMAP_PSIZE, MINIMAP_PSIZE);
	px = (uint32_t *)data->texture->imini_player->pixels;
	i = -1;
	while (++i < MINIMAP_PSIZE * MINIMAP_PSIZE)
		px[i] = 0xFF0000FF;
	mlx_image_to_window(data->mlx,
		data->texture->imini_player,
		data->mini_offset_x,
		data->mini_offset_y);
}

void render_player_minimap(t_data *data)
{
    if (!data->texture->imini_player)
        return;
    float scale = (float)MINIMAP_TILE / T_SIZE;
    int px = data->mini_offset_x + (int)(data->player->x * scale);
    int py = data->mini_offset_y + (int)(data->player->y * scale);
    if (data->texture->imini_player->count > 0)
    {
        data->texture->imini_player->instances[0].x = px;
        data->texture->imini_player->instances[0].y = py;
    }
}