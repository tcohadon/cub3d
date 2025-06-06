/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohadon <tcohadon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:06:03 by lmancho           #+#    #+#             */
/*   Updated: 2025/06/06 11:41:08 by tcohadon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_word(const char *str, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	if (!str)
		return (0);
	while (*str)
	{
		if (*str != c && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (*str == c)
			in_word = 0 ;
		str++;
	}
	return (count);
}

static char	*wordcpy(const char *str, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = (char *)malloc((end - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (start < end)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

static void	ft_freesplit(char **res, size_t j)
{
	if (!res)
		return ;
	while (j-- > 0)
		free(res[j]);
	if (res)
		free(res);
	res = NULL;
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	int		index;
	char	**res;

	i = -1;
	j = 0;
	res = (char **)malloc((count_word(s, c) + 1) * sizeof(char *));
	if (!res || !s)
		return (ft_freesplit(res, j), NULL);
	index = -1;
	while (++i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			res[j++] = wordcpy(s, index, i);
			if (!res[j - 1])
				return (ft_freesplit(res, j - 1), NULL);
			index = -1;
		}
	}
	res[j] = 0;
	return (res);
}
