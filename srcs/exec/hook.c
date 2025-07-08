/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cohadontom <cohadontom@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:26:26 by tcohadon          #+#    #+#             */
/*   Updated: 2025/07/08 10:31:31 by cohadontom       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	handle_rotation(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->player->angle -= 2.0f;
		if (data->player->angle < 0)
			data->player->angle += 360.0f;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->player->angle += 2.0f;
		if (data->player->angle >= 360.0f)
			data->player->angle -= 360.0f;
	}
}

void combined_hook(void *param)
{
	t_data *data;

	data = (t_data *)param;
	hooker(data);
	clear_rays(data);
	render(data);
	//minimap_hook(data);
	//raycasting_hook(data);
}