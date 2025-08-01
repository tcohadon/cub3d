/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitbox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohadon <tcohadon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:42:35 by tcohadon          #+#    #+#             */
/*   Updated: 2025/08/01 03:53:40 by tcohadon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	would_collide(t_data *data, double x, double y)
{
	int	grid_x;
	int	grid_y;

	grid_y = (int)(y) / T_SIZE;
	grid_x = (int)(x) / T_SIZE;
	return (grid_x < 0 || grid_y < 0 || !data->map[grid_y]
		|| !data->map[grid_y][grid_x] || data->map[grid_y][grid_x] == '1');
}

bool	check_hitbox_collision(t_data *data, double x, double y,
	double hitbox_rad)
{
	return (would_collide(data, x, y)
		|| would_collide(data, x + hitbox_rad, y)
		||would_collide(data, x - hitbox_rad, y)
		|| would_collide(data, x, y + hitbox_rad)
		|| would_collide(data, x, y - hitbox_rad)
		|| would_collide(data, x + hitbox_rad * 0.7, y + hitbox_rad * 0.7)
		|| would_collide(data, x - hitbox_rad * 0.7, y + hitbox_rad * 0.7)
		|| would_collide(data, x + hitbox_rad * 0.7, y - hitbox_rad * 0.7)
		|| would_collide(data, x - hitbox_rad * 0.7, y - hitbox_rad * 0.7));
}
