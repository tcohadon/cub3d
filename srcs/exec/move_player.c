/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohadon <tcohadon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 13:00:21 by tcohadon          #+#    #+#             */
/*   Updated: 2025/07/20 16:13:36 by tcohadon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static bool	would_collide(t_data *data, double x, double y)
{
	int	grid_x;
	int	grid_y;

	grid_y = (int)(y) / T_SIZE;
	grid_x = (int)(x) / T_SIZE;
	return (grid_x < 0 || grid_y < 0 || !data->map[grid_y]
		|| !data->map[grid_y][grid_x] || data->map[grid_y][grid_x] == '1');
}

static bool	check_hitbox_collision(t_data *data, double x, double y,
		double hitbox_radius)
{
	return (would_collide(data, x, y)
		||                                             // Center
			would_collide(data, x + hitbox_radius, y)
				||                             // Right
			would_collide(data, x - hitbox_radius, y)
				||                             // Left
			would_collide(data, x, y + hitbox_radius)
				||                             // Bottom
			would_collide(data, x, y - hitbox_radius)
				||                             // Top
			would_collide(data, x + hitbox_radius * 0.7, y + hitbox_radius
				* 0.7) || // Bottom-right
			would_collide(data, x - hitbox_radius * 0.7, y + hitbox_radius
				* 0.7) || // Bottom-left
			would_collide(data, x + hitbox_radius * 0.7, y - hitbox_radius
				* 0.7) || // Top-right
			would_collide(data, x - hitbox_radius * 0.7, y - hitbox_radius
				* 0.7));  // Top-left
}

static void	go_up(t_data *data)
{
	double	rad;
	double	nx;
	double	ny;
	double	hitbox_radius;

	hitbox_radius = PLAYER_SIZE / 2.0 * 1.2;
	rad = data->player->angle * PI / 180.0;
	nx = data->player->x + cos(rad) * data->player->speed;
	ny = data->player->y + sin(rad) * data->player->speed;
	// Try X movement
	if (!check_hitbox_collision(data, nx, data->player->y, hitbox_radius))
		data->player->x = nx;
	if (!check_hitbox_collision(data, data->player->x, ny, hitbox_radius))
		data->player->y = ny;
}

static void	go_down(t_data *data)
{
	double	rad;
	double	nx;
	double	ny;
	double	hitbox_radius;

	hitbox_radius = PLAYER_SIZE / 2.0 * 1.2;
	rad = (data->player->angle + 180.0) * PI / 180.0;
	nx = data->player->x + cos(rad) * data->player->speed;
	ny = data->player->y + sin(rad) * data->player->speed;
	// Try X movement
	if (!check_hitbox_collision(data, nx, data->player->y, hitbox_radius))
		data->player->x = nx;
	// Try Y movement (with potentially updated X position)
	if (!check_hitbox_collision(data, data->player->x, ny, hitbox_radius))
		data->player->y = ny;
}

static void	go_left(t_data *data)
{
	double	rad;
	double	nx;
	double	ny;
	double	hitbox_radius;

	hitbox_radius = PLAYER_SIZE / 2.0 * 1.2;
	rad = (data->player->angle - 90.0) * PI / 180.0;
	nx = data->player->x + cos(rad) * data->player->speed;
	ny = data->player->y + sin(rad) * data->player->speed;
	// Try X movement
	if (!check_hitbox_collision(data, nx, data->player->y, hitbox_radius))
		data->player->x = nx;
	// Try Y movement (with potentially updated X position)
	if (!check_hitbox_collision(data, data->player->x, ny, hitbox_radius))
		data->player->y = ny;
}

static void	go_right(t_data *data)
{
	double	rad;
	double	nx;
	double	ny;
	double	hitbox_radius;

	hitbox_radius = PLAYER_SIZE / 2.0 * 1.2;
	rad = (data->player->angle + 90.0) * PI / 180.0;
	nx = data->player->x + cos(rad) * data->player->speed;
	ny = data->player->y + sin(rad) * data->player->speed;
	// Try X movement
	if (!check_hitbox_collision(data, nx, data->player->y, hitbox_radius))
		data->player->x = nx;
	// Try Y movement (with potentially updated X position)
	if (!check_hitbox_collision(data, data->player->x, ny, hitbox_radius))
		data->player->y = ny;
}

void	hooker(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
	{
		free_all(data);
		exit(0);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT_SHIFT))
		data->player->speed = 3.0f;
	else
		data->player->speed = 2.0f;
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		go_up(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		go_down(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		go_left(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		go_right(data);
	handle_rotation(data);
}