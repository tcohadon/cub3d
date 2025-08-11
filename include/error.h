/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohadon <tcohadon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:48:59 by tcohadon          #+#    #+#             */
/*   Updated: 2025/08/11 13:53:28 by tcohadon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define ERR_ARG "Error\nBad arguments\n"
# define ERR_INVALID "Error\nInvalid character in map\n"
# define ERR_INITTEX "Error\nTexture is not initialized\n"
# define ERR_EXT "Error\nInvalid extension\n"
# define ERR_FILE "Error\nFile does not exist or you dont have permission\n"
# define ERR_ALLOC "Error\nMemory allocation failed\n"
# define ERR_SPLIT "Error\nFile is empty or split failed\n"
# define ERR_TOPWALL "Erorr\nMap is not closed on the top\n"
# define ERR_PLAYER "Error\nThere must be one and only one player\n"
# define ERR_WALKABLE "Error\nThere must be at least one walkable tile\n"
# define ERR_DUPLICATE "Error\nDuplicate texture\n"
# define ERR_LINE "Error\nInvalid line: %s"
# define ERR_BOTTOMWALL "Error\nWrong order/map is not closed on the bottom\n"
# define ERR_TEXTURES "Error\nMissing one or more textures\n"
# define ERR_LEFTWALL "Error\nMap is not closed on the left\n"
# define ERR_RIGHTWALL "Error\nMap is not closed on the right\n"
# define ERR_INVCHAR "Error\nInvalid characters on your map\n"
# define ERR_IMG "Error\nCannot load image\n"
# define ERR_SPACE "Error\nMap is not fully closed\n"
# define ERR_UNEX "Error\nUnexpected line: %s\n"
#endif