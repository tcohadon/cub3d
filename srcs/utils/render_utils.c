/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohadon <tcohadon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 01:22:40 by tcohadon          #+#    #+#             */
/*   Updated: 2025/08/01 03:55:47 by tcohadon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	calc_ray_params(t_data *data, int coll, double *ray_angle
	, int *wall_height)
{
	double	angle_rad;
	double	ratio;
	double	dist;

	*ray_angle = data->player->angle - (FOV / 2) + (coll * FOV / WIDTH);
	if (*ray_angle < 0)
		*ray_angle += 360;
	if (*ray_angle >= 360)
		*ray_angle -= 360;
	dist = ray_cast(data, *ray_angle);
	data->dda->wall_dist = dist;
	angle_rad = (*ray_angle - data->player->angle) * PI / 180.0;
	dist = dist * cos(angle_rad);
	if (dist < 0.1)
		dist = 0.1;
	ratio = (double)T_SIZE / dist;
	*wall_height = (int)(ratio * PROJECTION);
}

int	get_start_y(int w_height)
{
	int	start_y;

	start_y = (HEIGHT - w_height) / 2;
	if (start_y < 0)
		start_y = 0;
	return (start_y);
}

int	get_end_y(int w_height)
{
	int	end_y;

	end_y = (HEIGHT + w_height) / 2;
	if (end_y >= HEIGHT)
		end_y = HEIGHT - 1;
	return (end_y);
}

mlx_texture_t	*choose_texture(t_data *data, double *wall_x)
{
	mlx_texture_t	*tex;

	if (data->dda->hit_side == 0)
	{
		if (data->dda->ray_dir_x > 0)
			tex = data->texture->east_tex;
		else
			tex = data->texture->west_tex;
		*wall_x = data->player->y + data->dda->wall_dist * data->dda->ray_dir_y;
	}
	else
	{
		if (data->dda->ray_dir_y > 0)
			tex = data->texture->south_tex;
		else
			tex = data->texture->north_tex;
		*wall_x = data->player->x + data->dda->wall_dist * data->dda->ray_dir_x;
	}
	return (tex);
}

int	get_tex_x(t_data *data, mlx_texture_t *tex, double wall_x)
{
	int	tex_x;

	wall_x = fmod(wall_x, T_SIZE) / T_SIZE;
	if (wall_x < 0)
		wall_x += 1.0;
	tex_x = (int)(wall_x * (int)tex->width);
	if (tex_x < 0 || tex_x >= (int)tex->width)
		tex_x = 0;
	if ((data->dda->hit_side == 0 && data->dda->ray_dir_x < 0)
		|| (data->dda->hit_side == 1 && data->dda->ray_dir_y < 0))
		tex_x = (int)tex->width - tex_x - 1;
	return (tex_x);
}
