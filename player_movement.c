/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:20:50 by nsassenb          #+#    #+#             */
/*   Updated: 2023/10/11 18:15:23 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_move_player(t_player *player, t_point dir)
{
	player->pos.x += dir.x;
	player->pos.y += dir.y;
	return (0);
}

int	ft_check_player_move(t_game *game, t_point dir)
{
	char	newpos;

	newpos = ft_map_getat(&game->map,
			(t_point){game->player.pos.x + dir.x, game->player.pos.y + dir.y});
	if (newpos != '1' && newpos)
	{
		mlx_put_image_to_window(
			game->mlx_ptr, game->win_ptr, game->ground.img_ptr,
			game->player.pos.x * game->ground.size.x,
			game->player.pos.y * game->ground.size.y);
		ft_move_player(&game->player, dir);
		if (newpos == 'E' && game->map.ccount == game->player.collected)
			mlx_loop_end(game->mlx_ptr);
		else if (newpos == 'C')
		{
			game->map.lines[game->player.pos.y][game->player.pos.x] = '0';
			ft_printf("%i", game->player.collected++);
		}
		else if (newpos == 'G')
			ft_printf("Kill player\n");
	}
	return (0);
}
