/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_maps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmancho <lmancho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 12:37:50 by lmancho           #+#    #+#             */
/*   Updated: 2025/06/09 15:09:45 by lmancho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static bool	is_valid_char(char c)
{
    return (c == '0' || c == '1' || c == ' ' || c == 'N' || c == 'S'
        || c == 'E' || c == 'W');
}

bool	check_map_chars(t_game *game)
{
	int i;
	int j;
	int	player;

	i = 0;
	player = 0;
	while (game->map[i++])
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

void	final_check_map(t_game *game)
{
	if (!check_map_chars(game->map))
		exit(EXIT_FAILURE);
}