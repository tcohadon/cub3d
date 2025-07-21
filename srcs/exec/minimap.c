/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohadon <tcohadon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:59:04 by cohadontom        #+#    #+#             */
/*   Updated: 2025/07/21 15:47:58 by tcohadon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	init_miniplayer(t_data *data)
{
	int			i;
	uint32_t	*px;

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

void	init_minimap(t_data *data, int y)
{
	int			x;
	uint32_t	col;
	int			xx;
	int			yy;
	uint32_t	*bg;

	y = -1;
	data->texture->imini_player = NULL;
	data->texture->iminimap_bg = NULL;
	data->texture->iminimap_bg = mlx_new_image(data->mlx, data->w * MINIMAP_TILE, data->h * MINIMAP_TILE);
	bg = (uint32_t *)data->texture->iminimap_bg->pixels;
	while (++y < data->h)
	{
		x = -1;
		while (++x < data->w)
		{
			if (data->map[y][x] == '1')
				col = 0xFF0000FF;
			else
				col = 0xFFFFFFFF;
			yy = -1;
			while (++yy < MINIMAP_TILE)
			{
				xx = -1;
				while (++xx < MINIMAP_TILE)
					bg[(y * MINIMAP_TILE + yy) * data->w * MINIMAP_TILE + (x * MINIMAP_TILE + xx)] = col;
			}
		}
	}
	init_miniplayer(data);
}
