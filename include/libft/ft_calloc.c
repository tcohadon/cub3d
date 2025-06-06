/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohadon <tcohadon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:43:52 by lmancho           #+#    #+#             */
/*   Updated: 2025/06/06 11:41:08 by tcohadon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*alloc;
	size_t			i;

	if (size != 0 && nmemb > ((size_t)-1 / size))
		return (NULL);
	alloc = malloc (nmemb * size);
	if (!alloc)
		return (NULL);
	i = 0;
	while (i < nmemb * size)
	{
		alloc[i] = 0;
		i++;
	}
	return (alloc);
}
