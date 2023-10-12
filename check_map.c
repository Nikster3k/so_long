/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:56:26 by nsassenb          #+#    #+#             */
/*   Updated: 2023/10/12 19:58:54 by nsassenb         ###   ########.fr       */
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
			{
				map->pstart = (t_point){x, y};
				map->pcount++;
			}
			else if (map->lines[y][x] == 'E')
				map->ecount++;
			else if (!(map->lines[y][x] == '0' || map->lines[y][x] == '1'))
				return (INVALID_SIGNS);
			x++;
		}
		y++;
	}
	return (SUCCESS);
}

static void	ft_flood_fill(t_map *map, t_point pos, char tofill, t_point *count)
{
	if (pos.x >= map->size.x || pos.y >= map->size.y
		|| pos.y < 0 || pos.x < 0
		|| map->lines[pos.y][pos.x] == '1' || map->lines[pos.y][pos.x] == 'F')
		return ;
	if (map->lines[pos.y][pos.x] == 'C')
		count->x++;
	if (map->lines[pos.y][pos.x] == 'E')
		count->y++;
	map->lines[pos.y][pos.x] = 'F';
	ft_flood_fill(map, (t_point){pos.x + 1, pos.y}, tofill, count);
	ft_flood_fill(map, (t_point){pos.x, pos.y + 1}, tofill, count);
	ft_flood_fill(map, (t_point){pos.x - 1, pos.y}, tofill, count);
	ft_flood_fill(map, (t_point){pos.x, pos.y - 1}, tofill, count);
}

static int	ft_clone_map(t_map	*map, t_map *copy)
{
	int		i;

	*copy = *map;
	copy->lines = ft_calloc(sizeof(char *), map->size.y);
	if (copy->lines == NULL)
		return (MALLOC_FAIL);
	i = 0;
	while (i < copy->size.y)
	{
		copy->lines[i] = ft_strdup(map->lines[i]);
		if (copy->lines[i] == NULL)
		{
			ft_free_map(copy);
			return (MALLOC_FAIL);
		}
		i++;
	}
	return (SUCCESS);
}

int	ft_check_map(t_map *map)
{
	t_point	count;
	t_map	copy;
	int		err;

	count = (t_point){0, 0};
	err = SUCCESS;
	if (ft_check_validsigns(map))
		return (INVALID_SIGNS);
	if (map->pcount != 1 || map->ecount != 1 || map->ccount < 1)
		return (PLAYER_NUM);
	if (ft_clone_map(map, &copy))
		return (MALLOC_FAIL);
	ft_flood_fill(&copy, map->pstart, '0', &count);
	if (count.x != map->ccount || count.y == 0)
		err = INACCESSIBLE;
	if (ft_check_for_leaks(&copy))
		err = LEAK_MAP;
	ft_free_map(&copy);
	return (err);
}
