/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmancho <lmancho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:19:45 by lmancho           #+#    #+#             */
/*   Updated: 2025/08/02 12:09:17 by lmancho          ###   ########.fr       */
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
		if (!ft_isspace(line[i]))
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

void	free_textures(t_data *data)
{
	if (!data->texture)
		return ;
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

void	free_all(t_data *data)
{
	free_tab(data->map);
	free_tab(data->copy_map);
	free_tab(data->split_content);
	free(data->content_of_filename);
	if (data->texture)
		free_textures(data);
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

bool	is_valid_png(const char *filename)
{
	const char	*ext;
	int			fd;

	ext = ft_strchr(filename, '.');
	if (!ext || ft_strcmp(ext, ".png") != 0)
		return (fd_printf(2, "%s: %s\n", ERR_EXT, filename), false);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (fd_printf(2, "Cannot open file: %s\n", filename), false);
	close(fd);
	return (true);
}
