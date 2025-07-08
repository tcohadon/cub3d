/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cohadontom <cohadontom@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:59:04 by cohadontom        #+#    #+#             */
/*   Updated: 2025/07/08 10:27:43 by cohadontom       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	go_up(t_data *data)
{
	int	grid_x;
	int	grid_y;

	grid_x = (int)(data->player->mini_x) / T_SIZE;
	grid_y = (int)((data->player->mini_y - PLAYER_SIZE / 2.5f)
			- data->player->speed) / T_SIZE;
	if (!(grid_x < 0 || grid_y < 0 || !data->map[grid_y]
			|| !data->map[grid_y][grid_x]
		|| data->map[grid_y][grid_x] == '1'))
		data->player->mini_y -= data->player->speed;
}

static void	go_down(t_data *data)
{
	int	grid_x;
	int	grid_y;

	grid_x = (int)(data->player->mini_x) / T_SIZE;
	grid_y = (int)((data->player->mini_y + PLAYER_SIZE / 2.5f)
			+ data->player->speed) / T_SIZE;
	if (!(grid_x < 0 || grid_y < 0 || !data->map[grid_y]
			|| !data->map[grid_y][grid_x]
		|| data->map[grid_y][grid_x] == '1'))
		data->player->mini_y += data->player->speed;
}

static void	go_left(t_data *data)
{
	int	grid_x;
	int	grid_y;

	grid_x = (int)((data->player->mini_x - PLAYER_SIZE / 2.5f)
			- data->player->speed) / T_SIZE;
	grid_y = (int)(data->player->mini_y) / T_SIZE;
	if (!(grid_x < 0 || grid_y < 0 || !data->map[grid_y]
			|| !data->map[grid_y][grid_x]
		|| data->map[grid_y][grid_x] == '1'))
		data->player->mini_x -= data->player->speed;
}

static void	go_right(t_data *data)
{
	int	grid_x;
	int	grid_y;

	grid_x = (int)((data->player->mini_x + PLAYER_SIZE / 2.5f)
			+ data->player->speed) / T_SIZE;
	grid_y = (int)(data->player->mini_y) / T_SIZE;
	if (!(grid_x < 0 || grid_y < 0 || !data->map[grid_y]
			|| !data->map[grid_y][grid_x]
		|| data->map[grid_y][grid_x] == '1'))
		data->player->mini_x += data->player->speed;
}

void	minimap_hook(t_data *data)
{
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
	render_player_minimap(data);
}