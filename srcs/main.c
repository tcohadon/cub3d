/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohadon <tcohadon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:22:51 by tcohadon          #+#    #+#             */
/*   Updated: 2025/07/26 15:26:46 by tcohadon         ###   ########.fr       */
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
	data->mini_offset_x = 0;
	data->player = NULL;
	data->mini_offset_y = 0;
}

int	main(int ac, char **av)
{
	t_data data;
	(void)av;

	if (ac != 2)
		return (fd_printf(2, ERR_ARG), 1);
	ft_memset(&data, 0, sizeof(t_data));
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
	data.mlx = mlx_init(WIDTH,HEIGHT, "cub3d", false);
	if (!data.mlx)
		return (1);
	if (!init_texture(&data) ||!parse_color(&data))
	{
		free_all(&data);
		return (1);
	}
	render_map(&data);
	//init_minimap(&data, -1);
	mlx_loop_hook(data.mlx, &combined_hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	free_all(&data);
	return (0);
}