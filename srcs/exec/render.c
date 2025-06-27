/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohadon <tcohadon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:48:00 by tcohadon          #+#    #+#             */
/*   Updated: 2025/06/27 13:37:30 by tcohadon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	render_player_minimap(t_data *data)
{
	int	px;
	int	py;

	px = (int)data->player->x - PLAYER_SIZE / 2;
	py = (int)data->player->y - PLAYER_SIZE / 2;
	data->texture->iplayer->instances[0].x = px;
	data->texture->iplayer->instances[0].y = py;

}

static void	init_player_pos(t_data *data, int x, int y, char angle)
{
	int	tile_px;
	int	tile_py;
	int	px;
	int	py;

	tile_px = x * T_SIZE;
	tile_py = y * T_SIZE;
	px = tile_px + (T_SIZE - PLAYER_SIZE) / 2;
	py = tile_py + (T_SIZE - PLAYER_SIZE) / 2;
	mlx_image_to_window(data->mlx, data->texture->ifloor, tile_px, tile_py);
	data->player->x = px + PLAYER_SIZE / 2;
	data->player->y = py + PLAYER_SIZE / 2;
	if (angle == 'N')
		data->player->angle = 270.0;
	else if (angle == 'S')
		data->player->angle = 90.0;
	else if (angle == 'W')
		data->player->angle = 180.0;
	else if (angle == 'E')
		data->player->angle = 0.0;
}

void	render_map(t_data *data)
{
	int			x;
	int			y;
	mlx_image_t	*image;

	y = -1;
	while (data->copy_map[++y])
	{
		x = -1;
		while (data->copy_map[y][++x])
		{
			image = NULL;
			if (data->copy_map[y][x] == '1')
				image = data->texture->iwall;
			else if (data->copy_map[y][x] == '0')
				image = data->texture->ifloor;
			else if (data->copy_map[y][x] == 'N' || data->copy_map[y][x] == 'S' ||
				data->copy_map[y][x] == 'E' || data->copy_map[y][x] == 'W')
				init_player_pos(data, x, y, data->copy_map[y][x]);
			//if (image)
			//	mlx_image_to_window(data->mlx, image, x * T_SIZE, y * T_SIZE);
		}
	}
	render_player(data);
}

void	render_player(t_data *data)
{
	if (!data->player->x || !data->player->y)
		return ;
//	mlx_image_to_window(data->mlx, data->texture->iplayer, data->player->x, data->player->y);
	data->player->x +=  PLAYER_SIZE / 2;
	data->player->y += PLAYER_SIZE / 2;
}

static void	render_wall(t_data *data, int coll, int w_height)
{
	int start_y;      // Point de départ du mur sur l'écran
	int end_y;        // Point de fin du mur sur l'écran
	int y;            // Position actuelle en Y lors du dessin
	uint64_t color;   // Couleur du pixel à dessiner
	// Centrer le mur verticalement (il commence à mi-hauteur - wall_height/2)
	start_y = (HEIGHT - w_height) / 2;
	if (start_y < 0)
		start_y = 0;
// Le mur se termine à mi-hauteur + wall_height/2
	end_y = (HEIGHT + w_height) / 2;
	if (end_y >= HEIGHT)
		end_y = HEIGHT - 1;
// Dessiner le plafond (tout ce qui est au-dessus du mur)
	y = 0;
	while (y < start_y)
	{
		mlx_put_pixel(data->texture->ray_img, coll, y, 0xFFFFFFFF);
		y++;
	}
	// Dessiner le mur (avec une couleur différente selon le côté)
	while (y < end_y)
	{
		// Couleur différente selon le côté du mur touché
		if (data->dda->hit_side == 0)
			color = 0xFFFF0000; // Rouge pour murs verticaux (E/W)
		else
			color = 0x00000FFF; // Rouge foncé pour murs horizontaux (N/S)
		mlx_put_pixel(data->texture->ray_img , coll, y, color);
		y++;
	}
	// Dessiner le sol (tout ce qui est en-dessous du mur)
	while (y < HEIGHT)
	{
		mlx_put_pixel(data->texture->ray_img, coll, y, 0xAA3456F); // Couleur du sol
		y++;
	}
}

void	render(t_data *data)
{
	int	coll;
	double	ray_angle;
	double	wall_dist;
	int		wall_height;
	double angle_rad;
	coll = -1;
	while (++coll < WIDTH)
	{
		ray_angle = data->player->angle - (FOV / 2) + (coll * FOV / WIDTH);
		if (ray_angle < 0)
			ray_angle += 360;
		if (ray_angle >= 360)
			ray_angle -= 360;
		wall_dist = ray_cast(data, ray_angle);
		angle_rad = (ray_angle - data->player->angle) * PI / 180.0;
		wall_dist = wall_dist * cos(angle_rad);
        if (wall_dist < 0.1)
            wall_dist = 0.1;

        // Calcul de la hauteur du mur
		double ratio = (double) T_SIZE / wall_dist;
        wall_height = (int)(ratio * PROJECTION);

        // Protection contre les murs trop grands
        if (wall_height > HEIGHT * 5)
            wall_height = HEIGHT * 5;
		printf("Ray %d: angle=%f, wall_dist=%f, wall_height=%d\n", coll, ray_angle, wall_dist, wall_height);
		render_wall(data, coll, wall_height);
	}
}
