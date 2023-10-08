/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:16:48 by nsassenb          #+#    #+#             */
/*   Updated: 2023/10/08 18:24:56 by nsassenb         ###   ########.fr       */
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

static char	*ft_strtrim_replace(char **str, const char *set)
{
	char	*new;

	new = ft_strtrim(*str, set);
	free(*str);
	*str = new;
	return (new);
}

static void	ft_failclear(t_map *map)
{
	ft_fullfree_ml(&map->mlist);
}

int	ft_read_map(t_map *map, const char *file)
{
	char	*line;
	int		linelen;
	int		fd;

	fd = open(file, O_RDONLY);
	linelen = 0;
	map->size = (t_point){0, 0};
	map->mlist = (t_ml){NULL, 0, 0};
	while (line != NULL)
	{
		line = get_next_line(fd);
		if (line != NULL)
			linelen = ft_strlen(ft_strtrim_replace(&line, "\n"));
		if (map->size.x == 0)
			map->size.x = linelen;
		if (map->size.x != linelen || !ft_ml_pushback(&map->mlist, line))
			return (close(fd), free(line), ft_failclear(map), 0);
		map->size.y++;
	}
	return (close(fd), 1);
}
