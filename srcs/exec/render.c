/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohadon <tcohadon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:48:00 by tcohadon          #+#    #+#             */
/*   Updated: 2025/08/02 11:46:25 by tcohadon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	draw_wall_tex_line(t_data *data, t_wall_tex_params *params, int y,
		int tex_y)
{
	uint32_t	color;

	if (tex_y >= 0 && tex_y < (int)params->tex->height && params->tex_x >= 0
		&& params->tex_x < (int)params->tex->width)
	{
		color = get_texture_pixel(params->tex, params->tex_x, tex_y);
		mlx_put_pixel(data->texture->ray_img, params->coll, y, color);
	}
}

static void	draw_wall_tex(t_data *data, t_wall_tex_params *params)
{
	int	y;
	int	tex_y;
	int	y_pos;

	y = params->start_y - 1;
	while (++y < params->end_y)
	{
		y_pos = y - (HEIGHT - params->w_height) / 2;
		tex_y = (int)(((double)y_pos / params->w_height) * params->tex->height);
		draw_wall_tex_line(data, params, y, tex_y);
	}
}

static void	render_wall(t_data *data, int coll, int w_height)
{
	t_wall_tex_params	params;
	int					y;
	int					y_floor;

	y = -1;
	fill_wall_params(data, &params, coll, w_height);
	while (++y < params.start_y)
		mlx_put_pixel(data->texture->ray_img, coll, y,
			data->texture->ceiling_hex);
	draw_wall_tex(data, &params);
	y_floor = params.end_y;
	while (++y_floor < HEIGHT)
		mlx_put_pixel(data->texture->ray_img, coll, y_floor,
			data->texture->floor_hex);
}

void	render(t_data *data)
{
	int		coll;
	double	ray_angle;
	int		wall_height;

	if (!data || !data->mlx || !data->texture)
		return ;
	if (data->texture->ray_img)
		mlx_delete_image(data->mlx, data->texture->ray_img);
	data->texture->ray_img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(data->mlx, data->texture->ray_img, 0, 0);
	coll = -1;
	while (++coll < WIDTH)
	{
		calc_ray_params(data, coll, &ray_angle, &wall_height);
		render_wall(data, coll, wall_height);
	}
}
