/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohadon <tcohadon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:19:07 by lmancho           #+#    #+#             */
/*   Updated: 2025/07/26 16:26:42 by tcohadon         ###   ########.fr       */
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

void	err_msg(char *str, int code)
{
	fd_printf(2, "%s\n", str);
	exit(code);
}

uint32_t	ft_hex_to_uint32(const char *str)
{
	uint32_t	result;
	int			i;
	char		c;

	if (!str)
		return (0);
	i = 0;
	result = 0;
	while (str[i])
	{
		c = str[i];
		if (c >= '0' && c <= '9')
			result = result * 16 + (c - '0');
		else if (c >= 'A' && c <= 'F')
			result = result * 16 + (c - 'A' + 10);
		else if (c >= 'a' && c <= 'f')
			result = result * 16 + (c - 'a' + 10);
		else
			break ;
		i++;
	}
	return (result);
}

static char	*ft_str_to_hex(char *str)
{
	unsigned int	num;
	char			*hex_str;
	const char		*hex_digits = "0123456789ABCDEF";

	if (!str || !*str)
		return (ft_strdup("00"));
	num = (unsigned int)ft_atoi(str);
	if (num > 255)
		num = 255;
	hex_str = (char *)malloc(sizeof(char) * 3);
	if (!hex_str)
		return (NULL);
	hex_str[2] = '\0';
	hex_str[0] = hex_digits[num / 16];
	hex_str[1] = hex_digits[num % 16];
	return (hex_str);
}

char	*ft_join_tab(char **tab)
{
	char	*res;
	char	*tmp;

	res = ft_strdup(tab[0]);
	tmp = ft_strjoin(res, tab[1]);
	free(res);
	res = ft_strdup(tmp);
	free(tmp);
	tmp = ft_strjoin(res, tab[2]);
	free(res);
	res = ft_strdup(tmp);
	free(tmp);
	free_tab(tab);
	return (res);
}

char	*ft_tab_to_hex(char **tab)
{
	char	**color_tab;
	char	*res;

	color_tab = (char **)malloc(sizeof(char *) * 4);
	color_tab[0] = ft_str_to_hex(tab[0]);
	if (!color_tab[0])
		return (NULL);
	color_tab[1] = ft_str_to_hex(tab[1]);
	if (!color_tab[1])
		return (NULL);
	color_tab[2] = ft_str_to_hex(tab[2]);
	if (!color_tab[2])
		return (NULL);
	color_tab[3] = NULL;
	res = (ft_join_tab(color_tab));
	if (!res)
		return (NULL);
	return (res);
}

bool	parse_color(t_data *data)
{
	char	**floor;
	char	**ceiling;
	char	*hex_floor;
	char	*hex_ceiling;

	if (!data || !data->texture->ceiling_color || !data->texture->floor_color)
		return (false);
	floor = ft_split(data->texture->floor_color, ',');
	if (!floor)
		return (false);
	ceiling = ft_split(data->texture->ceiling_color, ',');
	if (!ceiling)
		return (free(floor), false);
	hex_floor = ft_tab_to_hex(floor);
	if (!hex_floor)
		return (false);
	hex_ceiling = ft_tab_to_hex(ceiling);
	if (!hex_ceiling)
		return (false);
	data->texture->ceiling_hex = ft_hex_to_uint32(hex_ceiling);
	data->texture->floor_hex = ft_hex_to_uint32(hex_floor);
	printf("floor str : %s\nceiling str: %s\n", hex_floor, hex_ceiling);
	printf("floor: %u\nceiling: %u\n", data->texture->floor_hex,
		data->texture->ceiling_hex);
	return (true);
}
