/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:16:48 by nsassenb          #+#    #+#             */
/*   Updated: 2023/10/12 12:30:31 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static	int	line_count(const char *file, int *count)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NO_FILE);
	*count = 0;
	line = (char *)2;
	while (line != NULL)
	{
		line = get_next_line(fd);
		if (line != NULL)
			(*count)++;
		free(line);
	}
	close(fd);
	return (SUCCESS);
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
			close(fd);
			return (NOT_RECTANGLE);
		}
		if (line != NULL)
			map->lines[map->size.y++] = line;
	}
	close(fd);
	return (SUCCESS);
}

int	ft_read_map(t_map *map, const char *file)
{
	int		fd;
	int		linecount;

	ft_init_map(map);
	if (line_count(file, &linecount))
		return (NO_FILE);
	if (linecount < 2)
		return (INVALID_MAP);
	map->lines = ft_calloc(sizeof(char *), linecount);
	if (map->lines == NULL)
		return (MALLOC_FAIL);
	fd = open(file, O_RDONLY);
	if (ft_read_file(map, fd))
		return (NOT_RECTANGLE);
	return (SUCCESS);
}
