/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:16:48 by nsassenb          #+#    #+#             */
/*   Updated: 2023/10/06 18:13:08 by nsassenb         ###   ########.fr       */
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
		free(line);
		count++;
	}
	return (close(fd), count);
}

static void	ft_failclear(t_map *map)
{
	ft_clear_ml_data(&map->map);
}

int	ft_read_map(t_map *map, const char *file)
{
	char	*read;
	char	*line;
	int		linelen;
	int		fd;

	fd = open(file, O_RDONLY);
	linelen = 0;
	map->size = (t_point){0, 0};
	map->map = (t_ml){NULL, 0, 0};
	while (read != NULL)
	{
		read = get_next_line(fd);
		line = ft_strtrim(read, "\n");
		if (line != NULL)
			linelen = ft_strlen(line);
		if (map->size.x == 0)
			map->size.x = linelen;
		if (map->size.x != linelen)
		{
			return (close(fd), free(read), free(line), 0);
		}
		if (!ft_ml_pushback(&map->map, line))
			return (free(line), ft_failclear(map), 0);
		free(line);
		map->size.y++;
	}
	return (close(fd), 1);
}
