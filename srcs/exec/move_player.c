/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cohadontom <cohadontom@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 13:00:21 by tcohadon          #+#    #+#             */
/*   Updated: 2025/07/07 11:57:12 by cohadontom       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	go_up(t_data *data)
{
	double	rad;
	double	nx;
	double	ny;
	int		grid_x;
	int		grid_y;


	rad = data->player->angle * PI / 180.0;
	nx = data->player->x + cos(rad) * data->player->speed;
	ny = data->player->y + sin(rad) * data->player->speed;
	grid_x = (int)(nx) / T_SIZE;
	grid_y = (int)(ny) / T_SIZE;
	if (!(grid_x < 0 || grid_y < 0
			|| !data->map[grid_y]
			|| !data->map[grid_y][grid_x]
			|| data->map[grid_y][grid_x] == '1'))
	{
		data->player->x = nx;
		data->player->y = ny;
	}
}

static void	go_down(t_data *data)
{
	double	rad;
	double	nx;
	double	ny;
	int		grid_x;
	int		grid_y;


	rad = (data->player->angle + 180.0) * PI / 180.0;
	nx = data->player->x + cos(rad) * data->player->speed;
	ny = data->player->y + sin(rad) * data->player->speed;
	grid_x = (int)(nx) / T_SIZE;
	grid_y = (int)(ny) / T_SIZE;
	if (!(grid_x < 0 || grid_y < 0
			|| !data->map[grid_y]
			|| !data->map[grid_y][grid_x]
			|| data->map[grid_y][grid_x] == '1'))
	{
		data->player->x = nx;
		data->player->y = ny;
	}
}

static void	go_left(t_data *data)
{
	double	rad;
	double	nx;
	double	ny;
	int		grid_x;
	int		grid_y;


	rad = (data->player->angle - 90.0) * PI / 180.0;
	nx = data->player->x + cos(rad) * data->player->speed;
	ny = data->player->y + sin(rad) * data->player->speed;
	grid_x = (int)(nx) / T_SIZE;
	grid_y = (int)(ny) / T_SIZE;
	if (!(grid_x < 0 || grid_y < 0
			|| !data->map[grid_y]
			|| !data->map[grid_y][grid_x]
			|| data->map[grid_y][grid_x] == '1'))
	{
		data->player->x = nx;
		data->player->y = ny;
	}
}

static void	go_right(t_data *data)
{
	double	rad;
	double	nx;
	double	ny;
	int		grid_x;
	int		grid_y;


	rad = (data->player->angle + 90.0) * PI / 180.0;
	nx = data->player->x + cos(rad) * data->player->speed;
	ny = data->player->y + sin(rad) * data->player->speed;
	grid_x = (int)(nx) / T_SIZE;
	grid_y = (int)(ny) / T_SIZE;
	if (!(grid_x < 0 || grid_y < 0
			|| !data->map[grid_y]
			|| !data->map[grid_y][grid_x]
			|| data->map[grid_y][grid_x] == '1'))
	{
		data->player->x = nx;
		data->player->y = ny;
	}
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
	//render_player_minimap(data);
}
