/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohadon <tcohadon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:19:45 by lmancho           #+#    #+#             */
/*   Updated: 2025/07/26 15:45:38 by tcohadon         ###   ########.fr       */
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
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
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
		if (data->texture->north_tex)
			mlx_delete_texture(data->texture->north_tex);
		if (data->texture->south_tex)
			mlx_delete_texture(data->texture->south_tex);
		if (data->texture->west_tex)
			mlx_delete_texture(data->texture->west_tex);
		if (data->texture->east_tex)
			mlx_delete_texture(data->texture->east_tex);
		free(data->texture);
	}
	if (data->player)
	{
		free(data->player);
		data->player = NULL;
	}
	if (data->dda)
	{
		free(data->dda);
		data->dda = NULL;
	}
}

void	debug_data(t_data *data)
{
    printf("filename: %s\n", data->filename);
    printf("fd: %d\n", data->fd);
    printf("size_of_filename: %zu\n", data->size_of_filename);
    printf("content_of_filename: %s\n", data->content_of_filename ? "OK" : "NULL");
    printf("split_content: %s\n", data->split_content ? "OK" : "NULL");
    printf("h: %d, w: %d\n", data->h, data->w);
    printf("map: %s\n", data->map ? "OK" : "NULL");
    printf("copy_map: %s\n", data->copy_map ? "OK" : "NULL");
    if (data->texture)
    {
        printf("no_tex: %s\n", data->texture->no_tex);
        printf("so_tex: %s\n", data->texture->so_tex);
        printf("we_tex: %s\n", data->texture->we_tex);
        printf("ea_tex: %s\n", data->texture->ea_tex);
        printf("floor_color: %s\n", data->texture->floor_color);
        printf("ceiling_color: %s\n", data->texture->ceiling_color);
    }
    else
        printf("texture: NULL\n");
}
