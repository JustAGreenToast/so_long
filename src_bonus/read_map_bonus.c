/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 13:46:31 by pfontenl          #+#    #+#             */
/*   Updated: 2023/12/04 12:40:14 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static int	file_len(int fd)
{
	char	c;
	int		out;
	size_t	len;

	len = 0;
	out = read(fd, &c, 1);
	while (out > 0)
	{
		len++;
		out = read(fd, &c, 1);
	}
	if (out == -1)
		return (out);
	return (len);
}

static char	*copy_map(int fd, int len)
{
	char	*buff;
	int		out;

	buff = malloc(len + 1);
	if (!buff)
		exit(ERR_MALLOC);
	out = read(fd, buff, len);
	if (out == -1)
		error_exit(ERR_READ);
	buff[len] = '\0';
	return (buff);
}

char	*read_map(char *file)
{
	int		fd;
	int		len;
	char	*map;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_exit(ERR_READ);
	len = file_len(fd);
	if (len == -1)
		error_exit(ERR_READ);
	close(fd);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_exit(ERR_READ);
	map = copy_map(fd, len);
	close(fd);
	return (map);
}
