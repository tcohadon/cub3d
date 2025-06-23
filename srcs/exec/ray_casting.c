/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucas <ucas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:27:14 by tcohadon          #+#    #+#             */
/*   Updated: 2025/06/23 11:03:01 by ucas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

size_t	map_height(char **map)
{
	size_t	height;

	if (!map)
		return (0);
	height = 0;
	while (map[height])
		height++;
	return (height);
}

static void	cast_loop(t_data *data, float raydir_x, float raydir_y)
{
	float	ray_pos_x;
	float	ray_pos_y;
	float	distance;
	int		map_x;
	int		map_y;

	ray_pos_y = data->player->y;
	ray_pos_x = data->player->x;
	distance = 0;
	while (1)
	{
		ray_pos_x += raydir_x * 3.0;
		ray_pos_y += raydir_y * 3.0;
		distance += 3.0;
		map_x = (int)(ray_pos_x / T_SIZE);
		map_y = (int)(ray_pos_y / T_SIZE);
		if (map_y < 0 || map_x < 0 || map_y >= (int)map_height(data->map)
			|| map_x >= (int)ft_strlen(data->map[map_y]))
			break ;
		if (data->map[map_y][map_x] == '1')
			break ;
		mlx_put_pixel(data->texture->ray_img, (uint32_t)ray_pos_x,
			(uint32_t)ray_pos_y, 0x871F78);
	}
}

static void	cast_single_ray(t_data *data, float ray_angle)
{
	const float	ray_dir_x = cos(ray_angle * PI / 180.0);
	const float	ray_dir_y = sin(ray_angle * PI / 180.0);

	cast_loop(data, ray_dir_x, ray_dir_y);
}

void	clear_rays(t_data *data)
{
	if (!data || !data->mlx || !data->texture)
		return ;
	if (data->texture->ray_img)
		mlx_delete_image(data->mlx, data->texture->ray_img);
	data->texture->ray_img = mlx_new_image(data->mlx, data->w * T_SIZE,
			data->h * T_SIZE);
	mlx_image_to_window(data->mlx, data->texture->ray_img, 0, 0);
}

void	raycasting_hook(t_data *data)
{
	int		i;
	float	start_angle;
	float	current_angle;

	i = -1;
	if (data->player)
	{
		start_angle = data->player->angle - (FOV / 2);
		while (++i < NUM_RAYS)
		{
			current_angle = start_angle + ((float)i / NUM_RAYS) * FOV;
			cast_single_ray(data, current_angle);
		}
	}
}