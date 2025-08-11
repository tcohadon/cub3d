/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmancho <lmancho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 18:18:15 by tcohadon          #+#    #+#             */
/*   Updated: 2025/08/11 11:57:08 by lmancho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static bool	validate_single_value(const char *line, int *i)
{
	int	value;

	while (line[*i] == ' ')
		(*i)++;
	if (line[*i] == ',' || line[*i] == '\0')
		return (fd_printf(2, "Error\nInvalid color value: %s\n", line), false);
	if (!ft_isdigit(line[*i]))
		return (fd_printf(2, "Error\nInvalid color value: %s\n", line), false);
	value = ft_atoi(&line[*i]);
	if (value < 0 || value > 255)
		return (fd_printf(2, "Error\nInvalid color value: %s\n", line), false);
	while (line[*i] && ft_isdigit(line[*i]))
		(*i)++;
	return (true);
}

bool	validate_values(const char *line)
{
	int	i;
	int	value_count;

	i = 0;
	value_count = 0;
	while (line[i])
	{
		if (!validate_single_value(line, &i))
			return (false);
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

char	*trim_cpy(char *str, int j)
{
	int		i;
	char	*end;

	end = malloc(sizeof(char) * j + 1);
	if (!end)
		return (NULL);
	j = 0;
	i = -1;
	while (str[++i])
	{
		if (!ft_isspace(str[i]))
		{
			end[j] = str[i];
			j++;
		}
	}
	end[j] = '\0';
	return (end);
}

char	*trim_spaces(char *str)
{
	int	i;
	int	j;

	if (!str)
		return (NULL);
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (!ft_isspace(str[i]))
			j++;
	}
	i = -1;
	if (j == 0)
		return (NULL);
	return (trim_cpy(str, j));
}
