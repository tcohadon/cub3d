/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmancho <lmancho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:26:37 by tcohadon          #+#    #+#             */
/*   Updated: 2025/06/09 13:19:46 by lmancho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool file_exist(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (false);
	close(fd);
	return (true);
}


bool	parsing(int ac, char **av)
{
	if (ac != 2)
		return(fd_printf(2, ERR_ARG), false);
	if (!verif_ext(av[1]))
		return (fd_printf(2,ERR_EXT), false);
	if (!file_exist(av[1]))
		return (fd_printf(2, ERR_FILE), false);
	return (true);
}