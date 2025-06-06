/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohadon <tcohadon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:33:50 by tcohadon          #+#    #+#             */
/*   Updated: 2025/04/18 14:36:20 by tcohadon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FD_PRINTF_H
# define FD_PRINTF_H
# include <stdarg.h>
# include <unistd.h>

int	fd_printf(int fd, const char *format, ...);
int	fd_type(const char type, va_list args, int fd);
int	fd_putchar(char c, int fd);
int	fd_putstr(char *s, int fd);
int	fd_putnbr(int n, int fd);
int	fd_print_hex(unsigned int nb, const char format, int fd);
int	fd_ptr_print(unsigned long long nb, int fd);
int	fd_put_u(unsigned int nb, int fd);
#endif