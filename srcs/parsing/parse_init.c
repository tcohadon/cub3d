/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohadon <tcohadon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 11:25:47 by lmancho           #+#    #+#             */
/*   Updated: 2025/08/03 13:10:16 by tcohadon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	init_texture(t_data *data)
{
	if (!data->texture)
		return (fd_printf(2, ERR_INITTEX, 1), false);
	data->texture->ray_img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->texture->north_tex = mlx_load_png(data->texture->no_tex);
	data->texture->south_tex = mlx_load_png(data->texture->so_tex);
	data->texture->west_tex = mlx_load_png(data->texture->we_tex);
	data->texture->east_tex = mlx_load_png(data->texture->ea_tex);
	if (!data->texture->north_tex || !data->texture->south_tex
		|| !data->texture->west_tex || !data->texture->east_tex)
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
	data->split_content = split_keep_empty(data->content_of_filename, '\n');
	if (!data->split_content || !data->split_content[0])
		return (fd_printf(2, ERR_SPLIT), 0);
	return (1);
}

bool	handle_line(t_data *data, char *line)
{
	int	i;

	i = 0;
	line = trim_spaces(line);
	if (is_empty_line(line))
		return (free(line), true);
	while (line[i] && ft_isspace(line[i]))
		i++;
	printf("%s\n", line);
	if (ft_strnstr(line, "NO", 2))
		return (parse_texture(line, &data->texture->no_tex, "NO"));
	else if (ft_strnstr(line, "SO", 2))
		return (parse_texture(line, &data->texture->so_tex, "SO"));
	else if (ft_strnstr(line, "WE", 2))
		return (parse_texture(line, &data->texture->we_tex, "WE"));
	else if (ft_strnstr(line, "EA", 2))
		return (parse_texture(line, &data->texture->ea_tex, "EA"));
	else if (ft_strnstr(line, "F", 1))
		return (parse_colorutils(line, &data->texture->floor_color, "F"));
	else if (ft_strnstr(line, "C", 1))
		return (parse_colorutils(line, &data->texture->ceiling_color, "C"));
	else if (line[i] == '1')
		return (free(line), true);
	return (fd_printf(2, ERR_UNEX, line), free(line), false);
}

static bool	parse_ressources(t_data *data)
{
	int	i;

	i = 0;
	while (data->split_content[i])
	{
		if (!handle_line(data, data->split_content[i]))
			return (false);
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
	if (!data->texture->no_tex || !data->texture->so_tex
		|| !data->texture->we_tex || !data->texture->ea_tex
		|| !data->texture->floor_color || !data->texture->ceiling_color)
		return (fd_printf(2, ERR_TEXTURES), false);
	if (!parse_and_fill_map(data))
		return (false);
	data->dda = malloc(sizeof(t_dda));
	if (!data->dda)
		return (false);
	ft_memset(data->dda, 0, sizeof(t_dda));
	return (1);
}
