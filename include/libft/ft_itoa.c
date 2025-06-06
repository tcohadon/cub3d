/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohadon <tcohadon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:01:14 by lmancho           #+#    #+#             */
/*   Updated: 2025/06/06 11:41:08 by tcohadon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	size_count(long nb)
{
	size_t	len;

	len = 0;
	if (nb < 0)
	{
		nb *= -1;
		len = 1;
	}
	if (nb == 0)
		len = 1;
	else
	{
		while (nb)
		{
			nb /= 10;
			len++;
		}
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long			number;
	char			*str;
	size_t			len;
	int				sign;

	len = size_count((size_t)n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	number = (size_t)n;
	sign = 0;
	if (number < 0)
	{
		number *= -1;
		str[0] = '-';
		sign = 1;
	}
	str[len] = '\0';
	while (len > (size_t) sign)
	{
		str[len - 1] = number % 10 + '0';
		number /= 10;
		len--;
	}
	return (str);
}
