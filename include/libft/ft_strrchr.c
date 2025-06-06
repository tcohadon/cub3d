/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohadon <tcohadon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:16:57 by lmancho           #+#    #+#             */
/*   Updated: 2025/06/06 11:41:08 by tcohadon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int			i;
	char		chr;
	const char	*occ;

	occ = NULL;
	i = 0;
	chr = c;
	while (s[i] != '\0')
	{
		if (s[i] == chr)
			occ = &s[i];
		i++;
	}
	if (chr == '\0')
		return ((char *)&s[i]);
	return ((char *)occ);
}
