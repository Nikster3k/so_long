/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:16:48 by nsassenb          #+#    #+#             */
/*   Updated: 2023/10/17 16:28:26 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static	int	line_count(const char *file, int *count)
{
	int		fd;
	int		hasnl;
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
		{
			(*count)++;
			hasnl = (line[ft_strlen(line) - 1] == '\n');
		}
		free(line);
	}
	close(fd);
	if (hasnl)
		return (INVALID_MAP);
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

static int	ft_read_file(t_map *map, int fd)
{
	char	*line;
	int		linelen;
	int		err;

	line = (char *)2;
	err = SUCCESS;
	while (line != NULL)
	{
		line = get_next_line(fd);
		if (line != NULL)
			linelen = ft_safestrlen(ft_strtrim_replace(&line, "\n"));
		if (map->size.x == 0)
			map->size.x = linelen;
		if (map->size.x != linelen)
			err = NOT_RECTANGLE;
		if (line != NULL)
			map->lines[map->size.y++] = line;
	}
	if (err)
	{
		free(line);
		ft_free_map(map);
	}
	close(fd);
	return (err);
}

int	ft_read_map(t_map *map, const char *file)
{
	int		fd;
	int		err;
	int		linecount;

	ft_bzero(map, sizeof(t_map));
	err = line_count(file, &linecount);
	if (err)
		return (err);
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
