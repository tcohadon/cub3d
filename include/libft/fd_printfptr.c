/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_printfptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohadon <tcohadon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:43:35 by tcohadon          #+#    #+#             */
/*   Updated: 2025/06/06 11:42:46 by tcohadon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fd_printf.h"

static int	fd_ptr_len(unsigned long long nb)
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

static void	fd_putptr(unsigned long long nb, int fd)
{
	if (nb >= 16)
	{
		fd_putptr(nb / 16, fd);
		fd_putptr(nb % 16, fd);
	}
	else
	{
		if (nb <= 9)
			fd_putchar(nb + '0', fd);
		else
			fd_putchar(nb - 10 + 'a', fd);
	}
}

int	fd_ptr_print(unsigned long long nb, int fd)
{
	int	ptrlen;

	ptrlen = 0;
	if (nb == 0)
		return (write(fd, "(nil)", 5));
	ptrlen += write(fd, "0x", 2);
	fd_putptr(nb, fd);
	ptrlen += fd_ptr_len(nb);
	return (ptrlen);
}
