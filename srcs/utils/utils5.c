/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmancho <lmancho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 12:45:27 by tcohadon          #+#    #+#             */
/*   Updated: 2025/08/11 11:59:31 by lmancho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
    size_t	i;

    i = 0;
    while (i < n && src[i])
    {
        dest[i] = src[i];
        i++;
    }
    while (i < n)
    {
        dest[i] = '\0';
        i++;
    }
    return (dest);
}
