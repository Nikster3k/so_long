/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:16:48 by nsassenb          #+#    #+#             */
/*   Updated: 2023/10/09 18:20:33 by nsassenb         ###   ########.fr       */
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
	line = (char *)2;
	while (line != NULL)
	{
		line = get_next_line(fd);
		free(line);
		if (line != NULL)
			count++;
	}
	close(fd);
	return (count);
}

static char	*ft_strtrim_replace(char **str, const char *set)
{
	char	*new;

	new = ft_strtrim(*str, set);
	free(*str);
	*str = new;
	return (new);
}

static void	ft_init_map(t_map *map)
{
	map->size = (t_point){0, 0};
	map->ccount = 0;
	map->ecount = 0;
	map->pcount = 0;
}

static int	ft_read_file(t_map *map, int fd)
{
	char	*line;
	int		linelen;
	int		error;

	error = SUCCESS;
	line = (char *)2;
	while (line != NULL)
	{
		line = get_next_line(fd);
		if (line != NULL)
			linelen = ft_strlen(ft_strtrim_replace(&line, "\n"));
		if (map->size.x == 0)
			map->size.x = linelen;
		if (map->size.x != linelen)
		{
			free(line);
			ft_free_map(map);
			error = NOT_RECTANGLE;
			break ;
		}
		if (line != NULL)
			map->lines[map->size.y++] = line;
	}
	return (error);
}

int	ft_read_map(t_map *map, const char *file)
{
	int		fd;
	int		linecount;

	ft_init_map(map);
	linecount = line_count(file);
	if (linecount < 2)
		return (INVALID_MAP);
	map->lines = malloc(sizeof(char *) * linecount);
	if (map->lines == NULL)
		return (MALLOC_FAIL);
	fd = open(file, O_RDONLY);
	if (ft_read_file(map, fd))
		return (NOT_RECTANGLE);
	close(fd);
	return (SUCCESS);
}
