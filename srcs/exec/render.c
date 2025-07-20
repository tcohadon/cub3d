/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohadon <tcohadon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:48:00 by tcohadon          #+#    #+#             */
/*   Updated: 2025/07/20 16:52:29 by tcohadon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
	mlx_image_to_window(data->mlx, data->texture->iplayer, px, py);
	data->player->x = px + PLAYER_SIZE / 2;
	data->player->y = py + PLAYER_SIZE / 2;
	data->player->mini_x = data->player->x;
	data->player->mini_y = data->player->y;
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
			if (data->copy_map[y][x] == 'N' || data->copy_map[y][x] == 'S'
				|| data->copy_map[y][x] == 'E' || data->copy_map[y][x] == 'W')
				init_player_pos(data, x, y, data->copy_map[y][x]);
			if (image)
				mlx_image_to_window(data->mlx, image, x, y);
		}
	}
	render_player(data);
}

void	render_player(t_data *data)
{
	if (!data->player->x || !data->player->y)
		return ;
	data->player->x += PLAYER_SIZE / 2;
	data->player->y += PLAYER_SIZE / 2;
}
static void	render_wall(t_data *data, int coll, int w_height)
{
	int				start_y;
	int				end_y;
	int				y;
	mlx_texture_t	*tex;
	double			wall_x;
	int				tex_x;
	double			step;
	double			tex_pos;
	int				tex_y;
	int				pixel_index;
	uint8_t			r;
	uint8_t			g;
	uint8_t			b;
	uint8_t			a;
	uint32_t		color;

	// Déterminer quelle texture utiliser en fonction de l'orientation du mur
	if (data->dda->hit_side == 0)
	{
		// Mur vertical (E/W)
		if (data->dda->ray_dir_x > 0)
			tex = data->texture->east_tex;
		else
			tex = data->texture->west_tex;
		// Calculer la coordonnée X exacte du point d'impact
		wall_x = data->player->y + data->dda->wall_dist * data->dda->ray_dir_y;
	}
	else
	{
		// Mur horizontal (N/S)
		if (data->dda->ray_dir_y > 0)
			tex = data->texture->south_tex;
		else
			tex = data->texture->north_tex;
		// Calculer la coordonnée X exacte du point d'impact
		wall_x = data->player->x + data->dda->wall_dist * data->dda->ray_dir_x;
	}
	// Normaliser wall_x à [0,1] en prenant le module
	wall_x = fmod(wall_x, T_SIZE) / T_SIZE;
	if (wall_x < 0)
		wall_x += 1.0;
	// Calculer la coordonnée X de la texture
	tex_x = (int)(wall_x * (int)tex->width);
	if (tex_x < 0 || tex_x >= (int)tex->width)
		tex_x = 0; // Éviter les dépassements
	// Inverser la coordonnée X si nécessaire
	if ((data->dda->hit_side == 0 && data->dda->ray_dir_x < 0)
		|| (data->dda->hit_side == 1 && data->dda->ray_dir_y < 0))
		tex_x = (int)tex->width - tex_x - 1;
	// Calculer la position de début et de fin du mur sur l'écran
	start_y = (HEIGHT - w_height) / 2;
	if (start_y < 0)
		start_y = 0;
	end_y = (HEIGHT + w_height) / 2;
	if (end_y >= HEIGHT)
		end_y = HEIGHT - 1;
	// Dessiner le plafond en BLEU
	y = 0;
	while (y < start_y)
	{
		mlx_put_pixel(data->texture->ray_img, coll, y, 0xFF0000FF); // Bleu
		y++;
	}
	// Dessiner le mur texturé
	step = (double)(int)tex->height / w_height;
	tex_pos = 0;
	// Si le mur est plus grand que l'écran,ajuster la position de départ dans la texture
	if (w_height > HEIGHT)
		tex_pos = (w_height - HEIGHT) / 2.0 * step;
	else
		tex_pos = 0;
	while (y < end_y)
	{
		tex_y = (int)tex_pos;
		// S'assurer que tex_y est dans les limites
		if (tex_y >= (int)tex->height)
			tex_y = (int)tex->height - 1;
		tex_pos += step;
		// Vérification des limites pour éviter les accès hors tableau
		if (tex_y >= 0 && tex_y < (int)tex->height && tex_x >= 0
			&& tex_x < (int)tex->width)
		{
			// Accès aux pixels avec gestion du format RGBA
			pixel_index = (tex_y * (int)tex->width + tex_x) * 4;
			r = tex->pixels[pixel_index + 0];
			g = tex->pixels[pixel_index + 1];
			b = tex->pixels[pixel_index + 2];
			a = tex->pixels[pixel_index + 3];
			color = (r << 24) | (g << 16) | (b << 8) | a;
			// Assombrir les murs horizontaux pour l'effet 3D
			if (data->dda->hit_side == 1)
				color = (color >> 1) & 0x7F7F7F7F;
			mlx_put_pixel(data->texture->ray_img, coll, y, color);
		}
		else
		{
			// Pixel hors limites, utiliser une couleur de secours
			mlx_put_pixel(data->texture->ray_img, coll, y, 0xFFFF00FF);
				// Magenta en cas d'erreur
		}
		y++;
	}
	// Dessiner le sol en VERT
	while (y < HEIGHT)
	{
		mlx_put_pixel(data->texture->ray_img, coll, y, 0xFF00FF00); // Vert
		y++;
	}
}

void	render(t_data *data)
{
	int		coll;
	double	ray_angle;
	double	wall_dist;
	int		wall_height;
	double	angle_rad;
	double	ratio;

	coll = -1;
	while (++coll < WIDTH)
	{
		ray_angle = data->player->angle - (FOV / 2) + (coll * FOV / WIDTH);
		if (ray_angle < 0)
			ray_angle += 360;
		if (ray_angle >= 360)
			ray_angle -= 360;
		wall_dist = ray_cast(data, ray_angle);
		data->dda->wall_dist = wall_dist;
		angle_rad = (ray_angle - data->player->angle) * PI / 180.0;
		wall_dist = wall_dist * cos(angle_rad);
		if (wall_dist < 0.1)
			wall_dist = 0.1;
		ratio = (double)T_SIZE / wall_dist;
		wall_height = (int)(ratio * PROJECTION);
		// Protection contre les murs trop grands
		if (wall_height > HEIGHT * 5)
			wall_height = HEIGHT * 5;
		// printf("Ray %d: angle=%f, wall_dist=%f, wall_height=%d\n", coll,
		render_wall(data, coll, wall_height);
	}
}
