/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmancho <lmancho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:30:40 by tcohadon          #+#    #+#             */
/*   Updated: 2025/08/11 12:01:20 by lmancho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static bool	valid_ext(char *av)
{
	if (ft_strlen(av) != 4)
		return (false);
	if (!ft_strcmp(av, ".cub"))
		return (true);
	return (false);
}

bool	verif_ext(char *av)
{
	if (!av)
		return (false);
	av += ft_strlen(av) - 1;
	while (*av)
	{
		if (*av == '.')
			return (valid_ext(av));
		av--;
	}
	return (false);
}

bool	parse_texture(char *line, char **texture, const char *prefix)
{
    int		i;
    int		start;
    int		end;
    char	*path;

    if (*texture != NULL)
        return (fd_printf(2, ERR_DUPLICATE), false);
    i = ft_strlen(prefix);
    while (line[i] && ft_isspace(line[i]))
        i++;
    start = i;
    end = ft_strlen(line) - 1;
    while (end >= start && (ft_isspace(line[end]) || line[end] == '\n'))
        end--;
    if (start > end)
        return (fd_printf(2, "Error\nEmpty texture path\n"), false);
    path = malloc(end - start + 2);
    if (!path)
        return (false);
    int j = 0;
    while (start <= end)
    {
        path[j] = line[start];
        j++;
        start++;
    }
    path[j] = '\0';
    
    *texture = path;
    return (true);
}

bool	parse_colorutils(char *line, char **color, const char *prefix)
{
    int	i;

    i = ft_strlen(prefix);
    while (line[i] && ft_isspace(line[i]))
        i++;
    if (*color != NULL)
        return (fd_printf(2, ERR_DUPLICATE), false); // Ne pas libérer line ici !
    if (!validate_color_format(&line[i]))
        return (false); // Ne pas libérer line ici !
    *color = ft_strdup(&line[i]);
    return (*color != NULL);
}

bool	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W');
}
