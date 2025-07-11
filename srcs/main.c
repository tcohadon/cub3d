/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucas <ucas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:22:51 by tcohadon          #+#    #+#             */
/*   Updated: 2025/07/01 09:58:54 by ucas             ###   ########.fr       */
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
    data->player = malloc(sizeof(t_player));
    if (!data->player)
        return ;
    data->player->x = 0;
    data->player->y = 0;
    data->player->speed = 2.0f;
    data->player->is_moving = false;
    data->player->angle = 0.0;
    data->texture = malloc(sizeof(t_texture));
    if (!data->texture)
        return ;
    data->texture->ifloor = NULL;
    data->texture->iplayer = NULL;
    data->texture->iwall = NULL;
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
	data.mlx = mlx_init(data.w * T_SIZE, data.h * T_SIZE, "cub3d", false);
	if (!data.mlx)
		return (1);
	if (!init_texture(&data))
	{
		free_all(&data);
		return (1);
	}
	render_map(&data);
	mlx_loop_hook(data.mlx, &combined_hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	free_all(&data);
	return (0);
}