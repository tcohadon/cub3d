/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groscondetom.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmancho <lmancho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:30:40 by tcohadon          #+#    #+#             */
/*   Updated: 2025/06/23 15:02:52 by lmancho          ###   ########.fr       */
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
	int	i;

	i = 0;
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
