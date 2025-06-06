/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_printhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohadon <tcohadon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:40:54 by tcohadon          #+#    #+#             */
/*   Updated: 2025/06/06 11:42:46 by tcohadon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fd_printf.h"

static int	fd_hex_len(unsigned int nb)
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

static void	fd_putnbr_hex(unsigned int nb, const char format, int fd)
{
	if (nb >= 16)
	{
		fd_putnbr_hex(nb / 16, format, fd);
		fd_putnbr_hex(nb % 16, format, fd);
	}
	else
	{
		if (nb <= 9)
			fd_putchar(nb + '0', fd);
		else
		{
			if (format == 'x')
				fd_putchar(nb - 10 + 'a', fd);
			if (format == 'X')
				fd_putchar(nb - 10 + 'A', fd);
		}
	}
}

int	fd_print_hex(unsigned int nb, const char format, int fd)
{
	if (nb == 0)
		return (write(fd, "0", 1));
	else
		fd_putnbr_hex(nb, format, fd);
	return (fd_hex_len(nb));
}
