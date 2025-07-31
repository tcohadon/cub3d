/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmancho <lmancho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 12:37:50 by lmancho           #+#    #+#             */
/*   Updated: 2025/07/23 12:18:08 by lmancho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static bool	validate_map_chars(t_data *game, int *player, int *walkable)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (!is_valid_char(game->map[i][j]))
				return (fd_printf(2, ERR_INVALID, 1), false);
			if (game->map[i][j] == 'N' || game->map[i][j] == 'S'
				|| game->map[i][j] == 'E' || game->map[i][j] == 'W')
			{
				(*walkable)++;
				(*player)++;
			}
			else if (game->map[i][j] == '0')
				(*walkable)++;
			j++;
		}
		i++;
	}
	return (true);
}

static bool	check_map_chars(t_data *game)
{
	int	player;
	int	walkable;

	player = 0;
	walkable = 0;
	if (!validate_map_chars(game, &player, &walkable))
		return (false);
	if (player != 1)
		return (fd_printf(2, ERR_PLAYER), false);
	if (walkable == 0)
		return (fd_printf(2, ERR_WALKABLE), false);
	return (true);
}

static bool	check_map_border_top(t_data *data)
{
	int	i;
	int	last;

	i = 0;
	while (data->map[0][i])
	{
		if (data->map[0][i] != ' ' && data->map[0][i] != '1')
			return (fd_printf(2, ERR_TOPWALL, 1), false);
		i++;
	}
	last = data->h - 1;
	i = 0;
	while (data->map[last][i])
	{
		if (data->map[last][i] != ' ' && data->map[last][i] != '1')
			return (fd_printf(2, ERR_BOTTOMWALL, 1), false);
		i++;
	}
	return (true);
}

static bool	check_map_lr(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	while (data->map[x])
	{
		y = 0;
		while (data->map[x][y] && data->map[x][y] == ' ')
			y++;
		if (data->map[x][y] != '1')
			return (fd_printf(2, ERR_LEFTWALL, 1), false);
		y = 0;
		while (data->map[x][y + 1])
			y++;
		while (data->map && data->map[x][y] == ' ')
			y--;
		if (data->map[x][y] != '1')
			return (fd_printf(2, ERR_RIGHTWALL, 1), false);
		x++;
	}
	return (true);
}

bool	verify_map(t_data *data)
{
	if (!check_map_border_top(data))
		return (false);
	if (!check_map_lr(data))
		return (false);
	if (!check_map_chars(data))
		return (false);
	return (true);
}
