/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmancho <lmancho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 12:37:50 by lmancho           #+#    #+#             */
/*   Updated: 2025/06/18 10:14:29 by lmancho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static bool	is_valid_char(char c)
{
    return (c == '0' || c == '1' || c == ' ' || c == 'N' || c == 'S'
        || c == 'E' || c == 'W');
}

static bool	check_map_chars(t_data *game)
{
	int	i;
	int	j;
	int	player;

	i = 0;
	player = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (!is_valid_char(game->map[i][j]))
				return (fd_printf(2, "Error\nInvalid character in map\n"), false);
			if (game->map[i][j] == 'N' || game->map[i][j] == 'S'
				|| game->map[i][j] == 'E' || game->map[i][j] == 'W')
			{
				player++;
				if (player > 1)
					return (fd_printf(2, "Error\nMultiple players in map\n"), false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

static bool	check_map_border_top(t_data *data)
{
	int i;
	int last;

	i = 0;
	while (data->map[0][i])
	{
		if (data->map[0][i] != ' ' && data->map[0][i] != '1')
			err_msg(ERR_TOPWALL, false);
		i++;	
	}
	last = data->h - 1;
	i = 0;
	while (data->map[last][i])
	{
		if (data->map[last][i] != ' ' && data->map[last][i] != '1')
			err_msg(ERR_BOTTOMWALL, false);
		i++;
	}
	return (true);
}

static bool	check_map_lr(t_data *data)
{
	int	x;
	int y;

	x = 0;
	while (data->map[x])
	{
		y = 0;
		while (data->map[x][y] && data->map[x][y] == ' ')
			y++;
		if (data->map[x][y] != '1')
			err_msg(ERR_LEFTWALL, false);
		x++;
	}
	x = 0;
	while (data->map[x])
	{
		y = 0;
		while (data->map[x][y + 1])
			y++;
		while (data->map && data->map[x][y] == ' ')
			y--;
		if (data->map[x][y] != '1')
			err_msg(ERR_RIGHTWALL, false);
		x++;
	}
	return (true);
}

bool	verify_map(t_data *data)
{
    if (!check_map_border_top(data))
        return (false);
    if (!check_map_lr(data))
        return false;
    if (!check_map_chars(data))
        return false;
    return true;
}