/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmancho <lmancho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 11:19:19 by ucas              #+#    #+#             */
/*   Updated: 2025/06/23 12:49:44 by lmancho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static bool	is_valid_character(char c)
{
	return ((c >= '0' && c <= '9') || c == ',' || c == ' ');
}

static bool	count_commas(const char *line)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (line[i])
    {
        if (line[i] == ',')
            count++;
        else if (!is_valid_character(line[i]))
            return (fd_printf(2, "Error\nInvalid character in color: %s\n", line), false);
        i++;
    }
    if (count != 2)
		return (fd_printf(2, "Error\nInvalid color format: %s\n", line), false);
	return (true);
}

static bool	validate_values(const char *line)
{
    int	i = 0;
    int	value_count = 0;

    while (line[i])
    {
        while (line[i] == ' ')
            i++;
        if (line[i] == ',' || line[i] == '\0')
            return (fd_printf(2, "Error\nInvalid color value: %s\n", line), false);
        if (!ft_isdigit(line[i]))
            return (fd_printf(2, "Error\nInvalid color value: %s\n", line), false);
        int value = ft_atoi(&line[i]);
        if (value < 0 || value > 255)
            return (fd_printf(2, "Error\nInvalid color value: %s\n", line), false);
        while (line[i] && ft_isdigit(line[i]))
            i++;
        value_count++;
        while (line[i] == ' ')
            i++;
        if (line[i] == ',')
            i++;
    }
    if (value_count != 3)
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