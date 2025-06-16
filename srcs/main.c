/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmancho <lmancho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:22:51 by tcohadon          #+#    #+#             */
/*   Updated: 2025/06/16 14:50:05 by lmancho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_0(t_data *data, char *map_path)
{
    data->fd = -1;
    data->path = map_path;
    data->h = 0;
    data->w = 0;
    data->map = NULL;
    data->copy_map = NULL;
    data->split_content = NULL;
    data->texture = NULL;
    data->content_of_filename = NULL;
    data->img = NULL;
}

int	main(int ac, char **av)
{
	t_data data;
	(void)av;
	
	if (ac != 2)
		return (fd_printf(2, ERR_ARG), 1);
	init_0(&data, av[1]);
	if (!parsing(ac, av))
	{
		free_all(&data);
		return (1);
	}
	if (!init_data(&data, av))
	{
		free_all(&data);
		return (1);
	}
	free_all(&data);
}