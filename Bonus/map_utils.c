/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 17:11:50 by nsassenb          #+#    #+#             */
/*   Updated: 2023/10/16 12:07:38 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_pos_isvalid(t_map *map, t_point pos)
{
	char	a;

	a = ft_map_getat(map, pos);
	if (a == '\0' || a == '1' || a == 'X')
		return (0);
	return (1);
}

t_point	ft_getposof(t_map *map, char c)
{
	t_point	iter;

	iter = (t_point){0, 0};
	while (iter.y < map->size.y)
	{
		iter.x = 0;
		while (iter.x < map->size.x)
		{
			if (map->lines[iter.y][iter.x] == c)
				return (iter);
			iter.x++;
		}
		iter.y++;
	}
	return ((t_point){-1, -1});
}
