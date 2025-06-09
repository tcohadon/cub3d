/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_maps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmancho <lmancho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 12:37:50 by lmancho           #+#    #+#             */
/*   Updated: 2025/06/09 13:18:43 by lmancho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static bool	is_valid_char(char c)
{
	if (c == '0' || c == '1' || c == ' ' || c == 'N' || c == 'S' 
		|| c == 'E' || c == 'W');
		return (true);
	return (false);
}

static bool	is_valid_line(const char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (!is_valid_char(line[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	parse_cub_file(const char *filename, t_data *map)
{
	int fd;
	char *line;
	
	fd = open(map->path, O_RDONLY);
	if (fd < 0)
		return (fd_printf(2, "Error\nCould not open file\n"), false);
	line = get_next_line(fd);
	while (line)
}