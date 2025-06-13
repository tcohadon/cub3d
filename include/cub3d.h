/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmancho <lmancho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:11:05 by tcohadon          #+#    #+#             */
/*   Updated: 2025/06/13 15:40:45 by lmancho          ###   ########.fr       */
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

# define TILE_SIZE 30
# define PLAYER_SIZE 12



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
	mlx_texture_t	*player_texture;
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
	char 	**copy_map;
	char		*content_of_filename;
	size_t		size_of_filename;
	char		**split_content;
	mlx_image_t	*img;
	t_texture	*texture;
}t_data;


#endif