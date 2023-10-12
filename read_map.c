/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:16:00 by nsassenb          #+#    #+#             */
/*   Updated: 2023/10/12 19:53:27 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_free_map_strings(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->size.y)
		free(map->lines[i++]);
}

void	ft_free_map(t_map *map)
{
	ft_free_map_strings(map);
	free(map->lines);
}

char	ft_map_getat(t_map *map, t_point pos)
{
	if (pos.x >= map->size.x || pos.x < 0
		|| pos.y >= map->size.y || pos.y < 0)
		return ('\0');
	return (map->lines[pos.y][pos.x]);
}

int	ft_create_map(t_map *map, const char *filepath)
{
	int	err;

	err = ft_read_map(map, filepath);
	if (err)
		return (err);
	err = ft_check_map(map);
	if (err)
		ft_free_map(map);
	return (err);
}
