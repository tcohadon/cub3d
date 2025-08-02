/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmancho <lmancho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 18:18:15 by tcohadon          #+#    #+#             */
/*   Updated: 2025/08/02 17:41:05 by lmancho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static bool	validate_single_value(const char *line, int *i)
{
	int	value;

	while (line[*i] == ' ')
		(*i)++;
	if (line[*i] == ',' || line[*i] == '\0')
		return (fd_printf(2, "Error\nInvalid color value: %s\n", line), false);
	if (!ft_isdigit(line[*i]))
		return (fd_printf(2, "Error\nInvalid color value: %s\n", line), false);
	value = ft_atoi(&line[*i]);
	if (value < 0 || value > 255)
		return (fd_printf(2, "Error\nInvalid color value: %s\n", line), false);
	while (line[*i] && ft_isdigit(line[*i]))
		(*i)++;
	return (true);
}

bool	validate_values(const char *line)
{
	int	i;
	int	value_count;

	i = 0;
	value_count = 0;
	while (line[i])
	{
		if (!validate_single_value(line, &i))
			return (false);
		value_count++;
		while (line[i] == ' ')
			i++;
		if (line[i] == ',')
			i++;
	}
	if (value_count != 3)
		return (fd_printf(2, "Error\nInvalid color format: %s\n", line), false);
	return (true);
}

static char	*alloc_segment(const char *str, int start, int end)
{
	char	*dst;
	int		j;

	dst = malloc(end - start + 1);
	if (!dst)
		return (NULL);
	j = 0;
	while (start < end)
	{
		dst[j] = str[start];
		j++;
		start++;
	}
	dst[j] = '\0';
	return (dst);
}

static int	count_separators(const char *str, char sep)
{
	int	count;
	int	i;

	count = 1;
	i = 0;
	while (str[i])
	{
		if (str[i] == sep)
			count++;
		i++;
	}
	return (count);
}

static void	fill_split(char **result, const char *str, char sep)
{
	int	i;
	int	start;
	int	idx;

	start = 0;
	idx = 0;
	i = 0;
	while (1)
	{
		if (str[i] == sep || str[i] == '\0')
		{
			result[idx] = alloc_segment(str, start, i);
			if (!result[idx])
				return ;
			idx++;
			start = i + 1;
			if (str[i] == '\0')
				break ;
		}
		i++;
	}
	result[idx] = NULL;
}

char	**split_keep_empty(const char *str, char sep)
{
	int		count;
	char	**result;

	count = count_separators(str, sep);
	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	fill_split(result, str, sep);
	return (result);
}
