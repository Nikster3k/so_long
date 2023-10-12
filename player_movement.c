/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:20:50 by nsassenb          #+#    #+#             */
/*   Updated: 2023/10/12 18:38:14 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_move_entity(t_entity *ent, t_point dir)
{
	ent->pos.x += dir.x;
	ent->pos.y += dir.y;
	return (0);
}

int	ft_check_player_move(t_game *game, t_point dir)
{
	char	newpos;

	newpos = ft_map_getat(&game->map, (t_point){
			game->player.ent.pos.x + dir.x, game->player.ent.pos.y + dir.y});
	if (newpos != '1' && newpos)
	{
		ft_draw_at(game, game->player.ent.pos);
		ft_move_entity(&game->player.ent, dir);
		ft_printf("Moves: %i\n", ++(game->player.moves));
		if (newpos == 'E' && game->map.ccount == game->player.collected)
			mlx_loop_end(game->mlx_ptr); //change to Victory function
		else if (newpos == 'C')
		{
			game->map.lines[game->player.ent.pos.y]
			[game->player.ent.pos.x] = '0';
			game->player.collected++;
		}
		else if (newpos == 'G')
			ft_printf("Kill player\n");
	}
	return (0);
}
