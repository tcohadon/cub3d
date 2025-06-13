/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmancho <lmancho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 11:25:47 by lmancho           #+#    #+#             */
/*   Updated: 2025/06/13 15:45:53 by lmancho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

//CHANGE LES RETURNS PAR DES FREE_ALL
static void	parse_file(t_data *data)
{
	char	buffer[1];

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
			data->texture->ceiling_color = ft_strdup(data->split_content + 2);
		i++;
	}
}

void	init_data(t_data *data, char **av)
{
	data = calloc(1, sizeof(t_data));
	if (!data)
		return (fd_printf(2, ERR_ALLOC), 0);
	data->filename = av[1];
	parse_file(data);
	parse_ressources(data);

}