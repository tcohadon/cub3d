/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohadon <tcohadon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:01:39 by tcohadon          #+#    #+#             */
/*   Updated: 2025/07/21 14:44:18 by tcohadon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_dda(t_data *data, double angle)
{
	if (!data)
		return ;
	data->dda->x_start = data->player->x;
	data->dda->y_start = data->player->y;
	data->dda->ray_dir_x = cos(angle * PI / 180.0);
	data->dda->ray_dir_y = sin(angle * PI / 180.0);
	data->dda->map_x = (int)(data->dda->x_start / T_SIZE);
	data->dda->map_y = (int)(data->dda->y_start / T_SIZE);
	data->dda->delta_dist_x = fabs(1.0 / data->dda->ray_dir_x);
	data->dda->delta_dist_y = fabs(1.0 / data->dda->ray_dir_y);
}

static double	ray_check(t_data *data, int side)
{
	double	wall_dist;

	if (side == 0)
		wall_dist = (data->dda->map_x - data->dda->x_start / T_SIZE
				+ (1 - data->dda->step_x) / 2) / data->dda->ray_dir_x;
	else
		wall_dist = (data->dda->map_y - data->dda->y_start / T_SIZE
				+ (1 - data->dda->step_y) / 2) / data->dda->ray_dir_y;
	data->dda->hit_side = side;
	data->dda->hit_x = data->dda->map_x;
	data->dda->hit_y = data->dda->map_y;
	return (wall_dist * T_SIZE);
}

static double	ray_dist(t_data *data, double side_dist_x, double side_dist_y)
{
	bool	hit;
	int		side;

	hit = false;
	while (!hit)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += data->dda->delta_dist_x;
			data->dda->map_x += data->dda->step_x;
			side = 0;
		}
		else
		{
			side_dist_y += data->dda->delta_dist_y;
			data->dda->map_y += data->dda->step_y;
			side = 1;
		}
		if (data->copy_map[data->dda->map_y][data->dda->map_x] == '1')
			hit = true;
	}
	return (ray_check(data, side));
}

double	ray_cast(t_data *data, double angle)
{
	double	side_dist_x;
	double	side_dist_y;

	init_dda(data, angle);
	if (data->dda->ray_dir_x < 0)
	{
		data->dda->step_x = -1;
		side_dist_x = (data->dda->x_start / T_SIZE - data->dda->map_x)
			* data->dda->delta_dist_x;
	}
	else
	{
		data->dda->step_x = 1;
		side_dist_x = (data->dda->map_x + 1.0 - data->dda->x_start / T_SIZE)
			* data->dda->delta_dist_x;
	}
	if (data->dda->ray_dir_y < 0)
	{
		data->dda->step_y = -1;
		side_dist_y = (data->dda->y_start / T_SIZE - data->dda->map_y)
			* data->dda->delta_dist_y;
	}
	else
	{
		data->dda->step_y = 1;
		side_dist_y = (data->dda->map_y + 1.0 - data->dda->y_start / T_SIZE)
			* data->dda->delta_dist_y;
	}
	return (ray_dist(data, side_dist_x, side_dist_y));
}
