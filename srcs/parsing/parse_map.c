/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohadon <tcohadon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:51:45 by lmancho           #+#    #+#             */
/*   Updated: 2025/07/21 13:16:58 by tcohadon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	find_map_start(char **split_content)
{
	int	i;
	int	j;

	i = 0;
	while (split_content[i])
	{
		j = 0;
		while (split_content[i][j] == ' ' || split_content[i][j] == '\t')
			j++;
		if (split_content[i][j] == '1')
			return (i);
		i++;
	}
	return (-1);
}

static int	find_map_end(char **split_content)
{
	int	i;

	i = 0;
	while (split_content[i])
		i++;
	i--;
	while (is_empty_line(split_content[i]))
		i--;
	return (i);
	return (-1);
}

static int	max_map_width(char **split_content, int start, int end)
{
	int	max;
	int	i;
	int	len;

	max = 0;
	i = start;
	while (i <= end)
	{
		len = ft_strlen(split_content[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

static void    fill_maps_from_split(t_data *data, int map_start)
{
    int i;
    int j;

    i = 0;
    while (i < data->h)
    {
        j = 0;
        while (data->split_content[map_start + i][j])
        {
            data->map[i][j] = data->split_content[map_start + i][j];
            data->copy_map[i][j] = data->split_content[map_start + i][j];
            j++;
        }
        while (j < data->w)
        {
            data->map[i][j] = ' ';
            data->copy_map[i][j] = ' ';
            j++;
        }
        data->map[i][j] = '\0';
        data->copy_map[i][j] = '\0';
        i++;
    }
    data->map[data->h] = NULL;
    data->copy_map[data->h] = NULL;
}

bool	parse_and_fill_map(t_data *data)
{
	int	map_start;
	int	map_end;

	map_start = find_map_start(data->split_content);
	map_end = find_map_end(data->split_content);
	if (map_start == -1 || map_end == -1 || map_end < map_start)
		exit(fd_printf(2, "Error\nInvalid map section\n"));
	data->h = map_end - map_start + 1;
	data->w = max_map_width(data->split_content, map_start, map_end);
	finalmap_allocation(data);
	fill_maps_from_split(data, map_start);
	if (!verify_map(data))
		return (false);
	if (!check_space_map(data))
		return (false);
	return (true);
}
