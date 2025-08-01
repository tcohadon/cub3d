/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohadon <tcohadon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:22:51 by tcohadon          #+#    #+#             */
/*   Updated: 2025/08/01 03:46:11 by tcohadon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	combined_hook(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	hooker(data);
	clear_rays(data);
	render(data);
}

static void	init_1(t_data *data)
{
	data->h = 0;
	data->w = 0;
	data->map = NULL;
	data->copy_map = NULL;
	data->split_content = NULL;
	data->texture = NULL;
	data->content_of_filename = NULL;
	data->img = NULL;
	data->mini_offset_x = 0;
	data->player = NULL;
	data->mini_offset_y = 0;
}

bool	init_0(t_data *data, char *map_path)
{
	data->fd = -1;
	data->path = map_path;
	init_1(data);
	if (!data->player)
	{
		data->player = malloc(sizeof(t_player));
		if (!data->player)
			return (fd_printf(2, ERR_ALLOC), false);
	}
	data->player->x = 0;
	data->player->y = 0;
	data->player->mini_x = 0;
	data->player->mini_y = 0;
	data->player->speed = 2.0f;
	data->player->is_moving = false;
	data->player->angle = 0.0;
	return (true);
}

static bool	parsing_space(int ac, char **av, t_data *data)
{
	if (!parsing(ac, av))
	{
		free_all(data);
		return (false);
	}
	if (!init_data(data, av))
	{
		free_all(data);
		return (false);
	}
	return (true);
}

int	main(int ac, char **av)
{
	t_data	data;

	(void)av;
	if (ac != 2)
		return (fd_printf(2, ERR_ARG), 1);
	ft_memset(&data, 0, sizeof(t_data));
	if (!init_0(&data, av[1]))
		free_all(&data);
	parsing_space(ac, av, &data);
	data.mlx = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	if (!data.mlx)
		return (1);
	if (!init_texture(&data) || !parse_color(&data))
	{
		free_all(&data);
		return (1);
	}
	init_player(&data);
	//init_minimap(&data, -1);
	mlx_loop_hook(data.mlx, &combined_hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	free_all(&data);
	return (0);
}
