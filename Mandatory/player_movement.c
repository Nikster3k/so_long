/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:20:50 by nsassenb          #+#    #+#             */
/*   Updated: 2023/10/14 20:31:19 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_move_entity(t_entity *ent, t_point dir)
{
	ent->pos.x += dir.x;
	ent->pos.y += dir.y;
	return (0);
}

void	ft_on_coin_collect(t_game *game)
{
	game->map.lines[game->player.ent.pos.y]
	[game->player.ent.pos.x] = '0';
	game->player.collected++;
	if (game->player.collected == game->map.ccount)
	{
		game->minmoves = ft_shortest_moves(
				&game->map, game->player.ent.pos, game->map.exitpos);
		game->savemoves = game->player.moves;
		ft_swap_img(game->mlx_ptr, &game->exit, "textures/ExitOpen.xpm");
		ft_draw_all(game);
	}
}

void	ft_on_exit(t_game *game)
{
	if (game->player.moves - game->savemoves > game->minmoves)
		ft_printf("You have not left in the minimum amount of moves\n");
	else
		ft_printf("Congratulations you beat the game!\n");
	mlx_loop_end(game->mlx_ptr);
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
			ft_on_exit(game);
		else if (newpos == 'C')
			ft_on_coin_collect(game);
	}
	return (0);
}
