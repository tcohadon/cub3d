/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmancho <lmancho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:11:05 by tcohadon          #+#    #+#             */
/*   Updated: 2025/08/02 12:09:39 by lmancho          ###   ########.fr       */
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
# define PI 3.14159265358979323846
# define FOV 60.0
# define WIDTH 960
# define HEIGHT 540
# define PROJECTION 831.4
# define MINIMAP_TILE 8
# define MINIMAP_PSIZE 4

typedef struct s_player
{
	float	x;
	float	y;
	float	speed;
	bool	is_moving;
	float	angle;
}	t_player;

typedef struct s_texture
{
	char			*no_tex;
	char			*so_tex;
	char			*we_tex;
	char			*ea_tex;
	char			*floor_color;
	char			*ceiling_color;
	uint32_t		floor_hex;
	uint32_t		ceiling_hex;
	mlx_image_t		*ray_img;
	mlx_texture_t	*north_tex;
	mlx_texture_t	*south_tex;
	mlx_texture_t	*west_tex;
	mlx_texture_t	*east_tex;
}	t_texture;

typedef struct s_dda
{
	double	x_start;
	double	y_start;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		hit_side;
	int		hit_x;
	int		hit_y;
	int		step_x;
	int		step_y;
	double	perp;

}	t_dda;

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
	t_dda		*dda;
}	t_data;

typedef struct s_wall_tex_params
{
	mlx_texture_t	*tex;
	int				tex_x;
	int				coll;
	int				w_height;
	int				start_y;
	int				end_y;
	double			step;
	double			tex_pos;
}	t_wall_tex_params;

//Parsing
bool			parsing(int ac, char **av);
bool			parse_and_fill_map(t_data *data);
bool			verif_ext(char *av);
bool			verify_map(t_data *data);
void			init_player(t_data *data);
bool			validate_color_format(const char *line);
bool			check_space_map(t_data *data);
bool			parse_color(t_data *data);

//Utils
bool			is_empty_line(char *line);
void			free_all(t_data *data);
int				ft_isspace(int c);
bool			validate_values(const char *line);
bool			is_valid_char(char c);
bool			handle_line(t_data *data, char *line);
bool			parse_texture(char *line, char **texture, const char *prefix);
bool			parse_colorutils(char *line, char **color, const char *prefix);
bool			is_valid_png(const char *filename);
bool			validate_resources(t_data *data);
void			free_tab(char **tab);

//Init
int				init_data(t_data *data, char **av);
bool			finalmap_allocation(t_data *map);

//movement
void			hooker(t_data *data);
void			handle_rotation(t_data *data);

//parsing
bool			parsing(int ac, char **av);
bool			verif_ext(char *av);
bool			init_texture(t_data *data);

//render
double			ray_cast(t_data *data, double angle);
void			render(t_data *data);

int				get_start_y(int w_height);
int				get_end_y(int w_height);
mlx_texture_t	*choose_texture(t_data *data, double *wall_x);
int				get_tex_x(t_data *data, mlx_texture_t *tex, double wall_x);
uint32_t		get_texture_pixel(mlx_texture_t *tex, int x, int y);
void			calc_ray_params(t_data *data, int coll, double *ray_angle,
					int *wall_height);
void			fill_wall_params(t_data *data, t_wall_tex_params *params,
					int coll, int w_height);
//hitbox
bool			check_hitbox_collision(t_data *data, double x, double y,
					double hitbox_rad);
bool			would_collide(t_data *data, double x, double y);
#endif
