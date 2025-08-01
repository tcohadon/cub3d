/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohadon <tcohadon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 02:20:42 by tcohadon          #+#    #+#             */
/*   Updated: 2025/08/01 03:53:46 by tcohadon         ###   ########.fr       */
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

void	fill_wall_params(t_data *data, t_wall_tex_params *params, int coll
	, int w_height)
{
	double			wall_x;
	mlx_texture_t	*tex;
	int				tex_x;

	tex = choose_texture(data, &wall_x);
	tex_x = get_tex_x(data, tex, wall_x);
	params->tex = tex;
	params->tex_x = tex_x;
	params->coll = coll;
	params->w_height = w_height;
	params->start_y = get_start_y(w_height);
	params->end_y = get_end_y(w_height);
}

uint32_t	get_texture_pixel(mlx_texture_t *tex, int x, int y)
{
	int		pixel_index;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	pixel_index = (y * tex->width + x) * 4;
	r = tex->pixels[pixel_index + 0];
	g = tex->pixels[pixel_index + 1];
	b = tex->pixels[pixel_index + 2];
	a = tex->pixels[pixel_index + 3];
	return ((r << 24) | (g << 16) | (b << 8) | a);
}
