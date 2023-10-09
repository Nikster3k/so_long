/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:56:26 by nsassenb          #+#    #+#             */
/*   Updated: 2023/10/09 16:33:23 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_check_validsigns(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->size.y)
	{
		x = 0;
		while (x < map->size.x)
		{
			if (map->lines[y][x] == 'C')
				map->ccount++;
			else if (map->lines[y][x] == 'P')
				map->pcount++;
			else if (map->lines[y][x] == 'E')
				map->ecount++;
			else if (map->lines[y][x] != '0' || map->lines[y][x] != '1')
				return (INVALID_SIGNS);
			x++;
		}
		y++;
	}
	return (SUCCESS);
}

t_point	ft_get_playerpos(t_map *map)
{
	int		x;
	int		y;

	y = 0;
	while (y < map->size.y)
	{
		x = 0;
		while (x < map->size.x)
		{
			if (map->lines[y][x] == 'P')
				return ((t_point){x, y});
			x++;
		}
		y++;
	}
	return ((t_point){-1, -1});
}

static void	ft_flood_fill(t_map *map, t_point pos, char tofill, t_point *count)
{
	if (pos.x < map->size.x || pos.y < map->size.y
		|| pos.y < 0 || pos.x < 0)
		return ;
	if (map->lines[pos.y][pos.x] == 'C')
		count->x++;
	if (map->lines[pos.y][pos.x] == 'E')
		count->y++;
	map->lines[pos.y][pos.x] = 'F';
	ft_flood_fill(map, (t_point){pos.x + 1, pos.y}, tofill, count);
	ft_flood_fill(map, (t_point){pos.x - 1, pos.y}, tofill, count);
	ft_flood_fill(map, (t_point){pos.x, pos.y + 1}, tofill, count);
	ft_flood_fill(map, (t_point){pos.x, pos.y - 1}, tofill, count);
}

int	ft_check_map(t_map *map)
{
	t_point	count;

	count = (t_point){0, 0};
	if (ft_check_validsigns(map) != 0)
		return (INVALID_SIGNS);
	if (map->pcount != 1 || map->ecount != 1)
		return (INVALID_SIGNS);
	ft_flood_fill(map, ft_get_playerpos(map), '0', &count);
	if (count.x != map->ccount || count.y == 0)
		return (INACCESIBLE);
	return (SUCCESS);
}
