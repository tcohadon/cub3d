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

void	free_textures(t_texture *texture)
{
	if (!texture)
		return ;
	free(texture->no_tex);
	free(texture->so_tex);
	free(texture->we_tex);
	free(texture->ea_tex);
	free(texture->floor_color);
	free(texture->ceiling_color);
	if (texture->north_tex)
		mlx_delete_texture(texture->north_tex);
	if (texture->south_tex)
		mlx_delete_texture(texture->south_tex);
	if (texture->west_tex)
		mlx_delete_texture(texture->west_tex);
	if (texture->east_tex)
		mlx_delete_texture(texture->east_tex);
	free(texture);
}

void	free_all(t_data *data)
{
	free_tab(data->map);
	free_tab(data->copy_map);
	free_tab(data->split_content);
	free(data->content_of_filename);
	if (data->texture)
		free_textures(data->texture);
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
