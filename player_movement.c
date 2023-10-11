/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tempNamePlayer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:20:50 by nsassenb          #+#    #+#             */
/*   Updated: 2023/10/11 14:33:54 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_move_player(t_entity *player, t_map *map, t_point dir)
{
	player->pos.x += dir.x;
	player->pos.y += dir.y;
	return (0);
}

int	ft_check_player_move(t_entity *player, t_map *map, t_point dir)
{
	char	newpos;

	newpos = ft_map_getat(map,
			(t_point){player->pos.x + dir.x, player->pos.y + dir.y});
	if (newpos != '1' && newpos)
	{
		ft_move_player(player, map, dir);
		if (newpos == 'E')
			ft_printf("Exit reached\n");
		else if (newpos == 'C')
			ft_printf("Collected collectable\n");
		else if (newpos == 'P')
			ft_printf("Kill player\n");
	}
	return (0);
}