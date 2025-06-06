/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohadon <tcohadon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:23:42 by lmancho           #+#    #+#             */
/*   Updated: 2025/06/06 11:43:45 by tcohadon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

static char	*clean_stash(char *stash)
{
	char	*new_stash;
	char	*ptr;
	int		len;

	ptr = ftft_strchr(stash, '\n');
	if (!ptr)
	{
		new_stash = NULL;
		return (ft_free(&stash));
	}
	else
		len = (ptr - stash) + 1;
	if (!stash[len])
		return (ft_free(&stash));
	new_stash = ftft_substr(stash, len, ftft_strlen(stash) - len);
	ft_free(&stash);
	if (!new_stash)
		return (NULL);
	return (new_stash);
}

static char	*new_line(char *stash)
{
	char	*line;
	char	*ptr;
	int		len;

	ptr = ftft_strchr(stash, '\n');
	len = (ptr - stash) + 1;
	line = ftft_substr(stash, 0, len);
	if (!line)
		return (NULL);
	return (line);
}

static char	*readbuf(int fd, char *stash)
{
	ssize_t		nbytes;
	char		*buffer;

	nbytes = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (ft_free(&stash));
	buffer[0] = '\0';
	while (nbytes > 0 && !ftft_strchr(buffer, '\n'))
	{
		nbytes = read (fd, buffer, BUFFER_SIZE);
		if (nbytes == 0)
			break ;
		if (nbytes > 0)
		{
			buffer[nbytes] = '\0';
			stash = ftft_strjoin(stash, buffer);
		}
	}
	free(buffer);
	if (nbytes == -1)
		return (ft_free(&stash));
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	if ((stash && !ftft_strchr(stash, '\n')) || !stash)
		stash = readbuf (fd, stash);
	if (!stash)
		return (NULL);
	line = new_line(stash);
	if (!line)
		return (ft_free(&stash));
	stash = clean_stash(stash);
	return (line);
}
