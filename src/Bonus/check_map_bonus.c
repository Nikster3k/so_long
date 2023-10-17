/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:56:26 by nsassenb          #+#    #+#             */
/*   Updated: 2023/10/17 15:59:33 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static int	ft_check_match(char c, const char *set)
{
	while (*set)
	{
		if (c == *(set++))
			return (1);
	}
	return (0);
}

static int	ft_check_validsigns(t_map *map)
{
	char	sign;
	int		x;
	int		y;

	y = 0;
	while (y < map->size.y)
	{
		x = 0;
		while (x < map->size.x)
		{
			sign = ft_map_getat(map, (t_point){x, y});
			if (!ft_check_match(sign, "01PCEG"))
				return (INVALID_SIGNS);
			map->ccount += (sign == COLLECTABLE);
			map->gcount += (sign == PATROL);
			map->ecount += (sign == EXIT);
			if (sign == PLAYER && map->pcount++ < 1)
				map->pstart = (t_point){x, y};
			x++;
		}
		y++;
	}
	return (SUCCESS);
}

static void	ft_flood_fill(t_map *map, t_point pos, char tofill, t_point *count)
{
	if (!ft_pos_isvalid(map, pos))
		return ;
	if (map->lines[pos.y][pos.x] == COLLECTABLE)
		count->x++;
	if (map->lines[pos.y][pos.x] == PLAYER)
		map->pstart = pos;
	if (map->lines[pos.y][pos.x] == EXIT)
	{
		count->y++;
		map->exitpos = pos;
	}
	map->lines[pos.y][pos.x] = 'X';
	ft_flood_fill(map, (t_point){pos.x + 1, pos.y}, tofill, count);
	ft_flood_fill(map, (t_point){pos.x, pos.y + 1}, tofill, count);
	ft_flood_fill(map, (t_point){pos.x - 1, pos.y}, tofill, count);
	ft_flood_fill(map, (t_point){pos.x, pos.y - 1}, tofill, count);
}

int	ft_clone_map(t_map	*map, t_map *copy)
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
	map->exitpos = copy.exitpos;
	if (ft_check_for_leaks(&copy))
		err = LEAK_MAP;
	ft_free_map(&copy);
	return (err);
}
