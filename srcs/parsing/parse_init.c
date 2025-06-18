/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmancho <lmancho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 11:25:47 by lmancho           #+#    #+#             */
/*   Updated: 2025/06/18 09:17:15 by lmancho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

//CHANGE LES RETURNS PAR DES FREE_ALL
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

static	void	parse_ressources(t_data *data)
{
	int i;

	i = 0;
	while (data->split_content[i])
	{
		if (ft_strnstr(data->split_content[i], "NO ", 3))
			data->texture->no_tex = ft_strdup(data->split_content[i] + 3);
		else if (ft_strnstr(data->split_content[i], "SO ", 3))
			data->texture->so_tex = ft_strdup(data->split_content[i] + 3);
		else if (ft_strnstr(data->split_content[i], "WE ", 3))
			data->texture->we_tex = ft_strdup(data->split_content[i] + 3);
		else if (ft_strnstr(data->split_content[i], "EA ", 3))
			data->texture->ea_tex = ft_strdup(data->split_content[i] + 3);
		else if (ft_strnstr(data->split_content[i], "F ", 2))
			data->texture->floor_color = ft_strdup(data->split_content[i] + 2);
		else if (ft_strnstr(data->split_content[i], "C ", 2))
			data->texture->ceiling_color = ft_strdup(data->split_content[i] + 2);
		i++;
	}
}

int	init_data(t_data *data, char **av)
{
	data->filename = av[1];
	data->texture = calloc(1, sizeof(t_texture));
	if (!data->texture)
		return (fd_printf(2, ERR_ALLOC), 0);
	parse_file(data);
	parse_ressources(data);
	parse_and_fill_map(data);
	debug_data(data);
	return (1);
}