/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:16:00 by nsassenb          #+#    #+#             */
/*   Updated: 2023/10/10 17:48:02 by nsassenb         ###   ########.fr       */
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

int	ft_create_map(t_map *map, char *filepath)
{
	int	err;

	err = ft_read_map(map, filepath);
	if (err)
	{
		ft_printf("failed map read\n");
		return (err);
	}
	err = ft_check_map(map);
	if (err)
	{
		ft_printf("Invalid map?\n");
		return (err);
	}
	else
		ft_printf("Valid map!\n");
	return (err);
}