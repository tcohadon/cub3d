/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_write_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohadon <tcohadon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:38:38 by tcohadon          #+#    #+#             */
/*   Updated: 2025/06/06 11:42:46 by tcohadon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fd_printf.h"

int	fd_putchar(char c, int fd)
{
	return (write(fd, &c, 1));
}

int	fd_putstr(char *s, int fd)
{
	size_t	i;

	i = 0;
	if (!s)
		return (write (fd, "(null)", 6));
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	return (i);
}

int	fd_putnbr(int n, int fd)
{
	int	count;

	count = 0;
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		count = 11;
	}
	else if (n < 0)
	{
		count += fd_putchar('-', fd);
		count += fd_putnbr(-n, fd);
	}
	else if (n >= 10)
	{
		count += fd_putnbr(n / 10, fd);
		count += fd_putnbr(n % 10, fd);
	}
	else
		count += fd_putchar(n + '0', fd);
	if (count < 0)
		return (-1);
	return (count);
}

int	fd_put_u(unsigned int nb, int fd)
{
	int	count;

	count = 0;
	if (nb > 9)
	{
		count += fd_putnbr(nb / 10, fd);
		count += fd_putnbr(nb % 10, fd);
	}
	else if (nb <= 9)
		count += fd_putchar(nb + '0', fd);
	return (count);
}
