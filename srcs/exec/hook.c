/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohadon <tcohadon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:26:26 by tcohadon          #+#    #+#             */
/*   Updated: 2025/07/21 14:48:34 by tcohadon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	handle_rotation(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->player->angle -= 2.0f;
		if (data->player->angle < 0)
			data->player->angle += 360.0f;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->player->angle += 2.0f;
		if (data->player->angle >= 360.0f)
			data->player->angle -= 360.0f;
	}
}

static void	render_minimap_on_image(t_data *data)
{
	int			y;
	int			x;
	uint32_t	col;
	float		scale;
	int			px;
	int			py;

	y = -1;
	while (++y < data->h)
	{
		x = -1;
		while (++x < data->w)
		{
			if (data->map[y][x] == '1')
			{
				col = 0xFFFFFFFF;
			}
			else
			{
				col = 0xFFAAAAAA;
			}
			for (int yy = 0; yy < MINIMAP_TILE; yy++)
				for (int xx = 0; xx < MINIMAP_TILE; xx++)
					mlx_put_pixel(data->texture->ray_img, data->mini_offset_x
						+ x * MINIMAP_TILE + xx, data->mini_offset_y + y
						* MINIMAP_TILE + yy, col);
		}
	}
	scale = (float)MINIMAP_TILE / T_SIZE;
	px = data->mini_offset_x + (int)(data->player->x * scale);
	py = data->mini_offset_y + (int)(data->player->y * scale);
	for (int yy = 0; yy < MINIMAP_PSIZE; yy++)
		for (int xx = 0; xx < MINIMAP_PSIZE; xx++)
			mlx_put_pixel(data->texture->ray_img, px + xx, py + yy, 0xFF0000FF);
}

void	combined_hook(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	hooker(data);
	clear_rays(data);
	render(data);
	render_minimap_on_image(data);
}
