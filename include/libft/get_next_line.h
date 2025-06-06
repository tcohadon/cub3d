/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmancho <lmancho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:23:50 by lmancho           #+#    #+#             */
/*   Updated: 2025/02/16 19:23:18 by lmancho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>

size_t	ftft_strlen(char *s);
char	*ft_free(char **str);
char	*ftft_strjoin(char *s1, char *s2);
char	*ftft_substr(char *s, unsigned int start, size_t len);
char	*ftft_strchr(char *s, int c);
char	*get_next_line(int fd);
#endif