/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_extra_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 12:46:20 by nsassenb          #+#    #+#             */
/*   Updated: 2023/10/17 18:01:24 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	ft_check_for_leaks(t_map *filled)
{
	int		x;
	int		y;

	x = 0;
	y = 1;
	while (x < filled->size.x)
	{
		if (filled->lines[filled->size.y - 1][x] != '1'
			|| filled->lines[0][x] != '1')
			return (LEAK_MAP);
		x++;
	}
	while (y < filled->size.y - 1)
	{
		if (filled->lines[y][filled->size.x - 1] != '1'
			|| filled->lines[y][0] != '1')
			return (LEAK_MAP);
		y++;
	}
	return (SUCCESS);
}
