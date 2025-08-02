/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmancho <lmancho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 11:19:19 by ucas              #+#    #+#             */
/*   Updated: 2025/08/02 12:08:38 by lmancho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static bool	is_valid_character(char c)
{
	return ((c >= '0' && c <= '9') || c == ',' || c == ' ');
}

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

static bool	count_commas(const char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == ',')
			count++;
		else if (!is_valid_character(line[i]))
			return (fd_printf(2, "Error\nInvalid character in color: %s\n",
					line), false);
		i++;
	}
	if (count != 2)
		return (fd_printf(2, "Error\nInvalid color format: %s\n", line), false);
	return (true);
}

bool	validate_color_format(const char *line)
{
	if (!count_commas(line))
		return (false);
	if (!validate_values(line))
		return (false);
	return (true);
}

bool	validate_resources(t_data *data)
{
	if (!is_valid_png(data->texture->no_tex)
		|| !is_valid_png(data->texture->so_tex)
		|| !is_valid_png(data->texture->we_tex)
		|| !is_valid_png(data->texture->ea_tex))
		return (false);
	return (true);
}
