/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmancho <lmancho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:19:45 by lmancho           #+#    #+#             */
/*   Updated: 2025/06/16 14:49:16 by lmancho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	is_empty_line(char *line)
{
	int	i;

	if (!line)
		return (true);
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
			return (false);
		i++;
	}
	return (true);
}

void	free_tab(char **tab)
{
    if (!tab)
        return;
    for (int i = 0; tab[i]; i++)
        free(tab[i]);
    free(tab);
}

void	free_all(t_data *data)
{
    free_tab(data->map);
    free_tab(data->copy_map);
    free_tab(data->split_content);
    free(data->content_of_filename);
    if (data->texture)
    {
        free(data->texture->no_tex);
        free(data->texture->so_tex);
        free(data->texture->we_tex);
        free(data->texture->ea_tex);
        free(data->texture->floor_color);
        free(data->texture->ceiling_color);
        free(data->texture);
    }
}

