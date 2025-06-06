/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohadon <tcohadon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:37:05 by lmancho           #+#    #+#             */
/*   Updated: 2025/06/06 11:42:37 by tcohadon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_type(const char type, va_list args)
{
	int	count;

	count = 0;
	if (type == 'c')
		count += ft_putchar(va_arg(args, int));
	else if (type == 's')
		count += ft_putstr(va_arg(args, char *));
	else if (type == 'p')
		count += ft_ptr_print(va_arg(args, unsigned long long));
	else if (type == 'd' || type == 'i')
		count += ft_putnbr(va_arg(args, int));
	else if (type == 'u')
		count += ft_put_u(va_arg(args, unsigned int));
	else if (type == 'x')
		count += ft_print_hex(va_arg(args, unsigned int), type);
	else if (type == 'X')
		count += ft_print_hex(va_arg(args, unsigned int), type);
	else if (type == '%')
		return (write(1, "%", 1));
	return (count);
}
