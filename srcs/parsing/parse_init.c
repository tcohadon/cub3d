/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohadon <tcohadon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 11:25:47 by lmancho           #+#    #+#             */
/*   Updated: 2025/07/26 16:03:20 by tcohadon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

//CHANGE LES RETURNS PAR DES FREE_ALL

bool	init_texture(t_data *data)
{
	data->texture->ray_img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->texture->north_tex = mlx_load_png(data->texture->no_tex);
	data->texture->south_tex = mlx_load_png(data->texture->so_tex);
	data->texture->west_tex = mlx_load_png(data->texture->we_tex);
	data->texture->east_tex = mlx_load_png(data->texture->ea_tex);
	if (!data->texture->north_tex || !data->texture->south_tex ||
		!data->texture->west_tex || !data->texture->east_tex)
		return (fd_printf(2, ERR_IMG, 1), false);
	return (true);
}

static int	parse_file(t_data *data)
{
	char	buffer[1];

	data->size_of_filename = 0;
	data->fd = open(data->filename, O_RDONLY);
	if (data->fd < 0)
		return (fd_printf(2, "Error opening file: %s\n", data->filename), 0);
	while (read(data->fd, buffer, 1))
		data->size_of_filename++;
	data->content_of_filename = malloc(data->size_of_filename + 1);
	if (!data->content_of_filename)
		return (fd_printf(2, ERR_ALLOC), 0);
	data->fd = open(data->filename, O_RDONLY);
	read(data->fd, data->content_of_filename, data->size_of_filename);
	data->content_of_filename[data->size_of_filename] = '\0';
	close(data->fd);
	data->split_content = ft_split(data->content_of_filename, '\n');
	if (!data->split_content || !data->split_content[0])
		return (fd_printf(2, ERR_SPLIT), 0);
	return (1);
}

static	bool	parse_ressources(t_data *data)
{
	int	i;

	i = 0;
	while (data->split_content[i])
	{
		if (ft_strnstr(data->split_content[i], "NO ", 3))
		{
			if (data->texture->no_tex != NULL)
				return (fd_printf(2, ERR_DUPLICATE), false);
			data->texture->no_tex = ft_strdup(data->split_content[i] + 3);
		}
		else if (ft_strnstr(data->split_content[i], "SO ", 3))
		{
			if (data->texture->so_tex != NULL)
				return (fd_printf(2, ERR_DUPLICATE), false);
			data->texture->so_tex = ft_strdup(data->split_content[i] + 3);
		}
		else if (ft_strnstr(data->split_content[i], "WE ", 3))
		{
			if (data->texture->we_tex != NULL)
				return (fd_printf(2, ERR_DUPLICATE), false);
			data->texture->we_tex = ft_strdup(data->split_content[i] + 3);
		}
		else if (ft_strnstr(data->split_content[i], "EA ", 3))
		{
			if (data->texture->ea_tex != NULL)
				return (fd_printf(2, ERR_DUPLICATE), false);
			data->texture->ea_tex = ft_strdup(data->split_content[i] + 3);
		}
		else if (ft_strnstr(data->split_content[i], "F ", 2))
		{
			if (data->texture->floor_color != NULL)
				return (fd_printf(2, ERR_DUPLICATE), false);
			if (!validate_color_format(data->split_content[i] + 2))
				return (false);
			data->texture->floor_color = ft_strdup(data->split_content[i] + 2);
		}
		else if (ft_strnstr(data->split_content[i], "C ", 2))
		{
			if (data->texture->ceiling_color != NULL)
				return (fd_printf(2, ERR_DUPLICATE), false);
			if (!validate_color_format(data->split_content[i] + 2))
				return (false);
			data->texture->ceiling_color = ft_strdup(data->split_content[i] + 2);
		}
		i++;
	}
	return (true);
}

int	init_data(t_data *data, char **av)
{
	data->filename = av[1];
	data->texture = ft_calloc(1, sizeof(t_texture));
	if (!data->texture)
		return (fd_printf(2, ERR_ALLOC), 0);
	if (!parse_file(data))
		return (false);
	if (!parse_ressources(data))
		return (false);
	if (!validate_resources(data))
		return (false);
	if (!data->texture->no_tex || !data->texture->so_tex ||
		!data->texture->we_tex || !data->texture->ea_tex ||
		!data->texture->floor_color || !data->texture->ceiling_color)
		return (fd_printf(2, ERR_TEXTURES), false);
	if (!parse_and_fill_map(data))
		return (false);
	//debug_data(data);
	if (!data->player)
	{
		data->player = malloc(sizeof(t_player));
		if (!data->player)
			return (fd_printf(2, ERR_ALLOC), 0);
	}
	data->player->x = 0;
	data->player->y = 0;
	data->player->mini_x = 0;
	data->player->mini_y = 0;
	data->player->speed = 2.0f;
	data->player->is_moving = false;
	data->player->angle = 0.0;
	data->dda = malloc(sizeof(t_dda));
	if (!data->dda)
		return (false);
	ft_memset(data->dda, 0, sizeof(t_dda));
	return (1);
}
