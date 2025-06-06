/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohadon <tcohadon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:11:03 by lmancho           #+#    #+#             */
/*   Updated: 2025/06/06 11:42:37 by tcohadon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_ptr_len(unsigned long long nb)
{
	int	len;

	len = 0;
	while (nb)
	{
		nb /= 16;
		len++;
	}
	return (len);
}

static void	ft_putptr(unsigned long long nb)
{
	if (nb >= 16)
	{
		ft_putptr(nb / 16);
		ft_putptr(nb % 16);
	}
	else
	{
		if (nb <= 9)
			ft_putchar(nb + '0');
		else
			ft_putchar(nb - 10 + 'a');
	}
}

int	ft_ptr_print(unsigned long long nb)
{
	int	ptrlen;

	ptrlen = 0;
	if (nb == 0)
		return (write(1, "(nil)", 5));
	ptrlen += write(1, "0x", 2);
	ft_putptr(nb);
	ptrlen += ft_ptr_len(nb);
	return (ptrlen);
}
