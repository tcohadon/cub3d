/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohadon <tcohadon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:24:43 by tcohadon          #+#    #+#             */
/*   Updated: 2025/06/06 11:42:46 by tcohadon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fd_printf.h"

int	fd_type(const char type, va_list args, int fd)
{
	int	count;

	count = 0;
	if (type == 'c')
		count += fd_putchar(va_arg(args, int), fd);
	else if (type == 's')
		count += fd_putstr(va_arg(args, char *), fd);
	else if (type == 'p')
		count += fd_ptr_print(va_arg(args, unsigned long long), fd);
	else if (type == 'd' || type == 'i')
		count += fd_putnbr(va_arg(args, int), fd);
	else if (type == 'u')
		count += fd_put_u(va_arg(args, unsigned int), fd);
	else if (type == 'x')
		count += fd_print_hex(va_arg(args, unsigned int), type, fd);
	else if (type == 'X')
		count += fd_print_hex(va_arg(args, unsigned int), type, fd);
	else if (type == '%')
		return (write(fd, "%", 1));
	return (count);
}

int	fd_printf(int fd, const char *format, ...)
{
	int		i;
	int		count;
	va_list	args;

	if (!format)
		return (-1);
	va_start (args, format);
	i = 0;
	count = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			count += fd_type(format[i], args, fd);
		}
		else
			count += fd_putchar(format[i], fd);
		i++;
	}
	va_end (args);
	return (count);
}
