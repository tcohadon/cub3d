/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cohadontom <cohadontom@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:19:07 by lmancho           #+#    #+#             */
/*   Updated: 2025/07/26 10:28:22 by cohadontom       ###   ########.fr       */
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
	exit (code);
}

static char	*ft_itoa_hex(int n)
{
	unsigned int	num;
	int				len;
	char			*hex_str;
	const char		*hex_digits = "0123456789ABCDEF";

	if (n == 0)
		return (ft_strdup("00"));
	num = (unsigned int)n;
	len = 0;
	while (num > 0)
	{
		num /= 16;
		len++;
	}
	hex_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!hex_str)
		return (NULL);
	hex_str[len] = '\0';
	num = (unsigned int)n;
	while (num > 0)
	{
		len--;
		hex_str[len] = hex_digits[num % 16];
		num /= 16;
	}
	return (hex_str);
}

bool join_color(t_data *data, bool tex, char **tab)
{
	int		red;
	int		green;
	int		blue;
	char	*color;
	char	*rgb;
	
	red = ft_atoi(tab[0]);
	green = ft_atoi(tab[1]);
	blue = ft_atoi(tab[2]);
	free_tab(tab);
	color = ft_itoa_hex(red);
	if (!color)
		return (false);
	rgb =  ft_strjoin("0x", color);
	free(color);
	color = ft_itoa_hex(green);
	if (!color)
		return (false);
}

bool parse_color(t_data *data)
{
	char	**floor;
	char	**ceiling;

	
	if (!data || !data->texture->ceiling_color || !data->texture->floor_color)
		return (false);
	floor = ft_split(data->texture->floor_color, ',');
	if (!floor)
		return(false);
	ceiling = ft_split(data->texture->ceiling_color, ',');
	if (!ceiling)
		return (false);
	if (!join_color(data, false, floor) || !join_color(data, true, ceiling))
		return (false);
}