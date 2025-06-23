/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucas <ucas@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:11:05 by tcohadon          #+#    #+#             */
/*   Updated: 2025/06/23 11:28:30 by ucas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "libft/libft.h"
# include "MLX42/include/MLX42/MLX42.h"
# include "error.h"

# define T_SIZE 50
# define PLAYER_SIZE 5
# define PI 3.1415926535
# define FOV 60.0
# define NUM_RAYS 1000

typedef struct s_player
{
	float	x;
	float	y;
	float target_x;
	float target_y;
	float speed;
	bool is_moving;
	float angle;
} t_player;


typedef struct s_texture
{
	char			*no_tex;
	char			*so_tex;
	char			*we_tex;
	char			*ea_tex;
	char			*floor_color;
	char			*ceiling_color;
	mlx_image_t		*ifloor;
	mlx_image_t		*iplayer;
	mlx_image_t		*iwall;
	mlx_texture_t	*player_texture;
	mlx_image_t		*ray_img;
}	t_texture;

typedef struct s_data
{
	void		*mlx;
	char		*filename;
	int			fd;
	int			h;
	char		*path;
	int			w;
	char		**map;
	char		**copy_map;
	char		*content_of_filename;
	size_t		size_of_filename;
	char		**split_content;
	mlx_image_t	*img;
	t_texture	*texture;
	t_player	*player;
}	t_data;

//Parsing
bool	parsing(int ac, char **av);
bool	parse_and_fill_map(t_data *data);
bool	verif_ext(char *av);
bool	verify_map(t_data *data);
void	render_map(t_data *data);
bool	validate_color_format(const char *line);
//Utils
bool	is_empty_line(char *line);
void	free_all(t_data *data);
void	debug_data(t_data *data);
void	err_msg(char *str, int code);

//Init
int		init_data(t_data *data, char **av);
void	finalmap_allocation(t_data *map);

//movement
void	hooker(t_data *data);
void	render_player_minimap(t_data *data);
void	handle_rotation(t_data *data);


//raycasting
void	raycasting_hook(t_data *data);
void	clear_rays(t_data *data);

//parsing
bool	parsing(int ac, char **av);
bool	verif_ext(char *av);
void combined_hook(void *param);
bool	init_texture(t_data *data);

//render
void	render_player(t_data *data);

#endif