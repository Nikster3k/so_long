/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:16:48 by nsassenb          #+#    #+#             */
/*   Updated: 2023/10/06 13:09:03 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <fcntl.h>

static	size_t	line_count(const char *file)
{
	int		fd;
	size_t	count;
	char	*line;

	fd = open(file, O_RDONLY);
	count = 0;
	while (line != NULL)
	{
		line = get_next_line(fd);
		count++;
	}
	return (close(fd), count);
}

t_map	read_map(const char *file)
{
	t_map	map;
	char	*line;
	int		linelen;
	int		fd;

	fd = open(file, O_RDONLY);
	map.map = malloc(sizeof(char *) * line_count(file));
	if (map.map == NULL)
		return (close(fd), map);
	linelen = 0;
	while (line != NULL)
	{
		line = get_next_line(fd);
		if (line != NULL)
			linelen = ft_strlen(line);
		if (map.size.x == 0)
			map.size.x = linelen;
		if (map.size.x != linelen)
		{
			while (map.size.y--)
				free(map.map[map.size.y]);
			return (close(fd), free(map.map), map);
		}
		map.map[map.size.y] = line;
		map.size.y++;
	}
	return (close(fd), map);
}
