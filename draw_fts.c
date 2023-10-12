/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:08:47 by nsassenb          #+#    #+#             */
/*   Updated: 2023/10/11 18:15:14 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_draw_map(t_game *game)
{
	t_point	iter;

	iter = (t_point){0, 0};
	while (iter.y < game->map.size.y)
	{
		iter.x = 0;
		while (iter.x < game->map.size.x)
		{
			if (ft_map_getat(&game->map, iter) == '1')
			{
				mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
					game->wall.img_ptr,
					iter.x * game->wall.size.x, iter.y * game->wall.size.y);
			}
			else if (ft_map_getat(&game->map, iter) == 'C')
				mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
					game->coin.img_ptr, iter.x * game->coin.size.x,
					iter.y * game->coin.size.y);
			else
				mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
					game->ground.img_ptr, iter.x * game->ground.size.x,
					iter.y * game->ground.size.y);
			iter.x++;
		}
		iter.y++;
	}
}

void	ft_draw_player(t_game *game)
{
	mlx_put_image_to_window(
		game->mlx_ptr, game->win_ptr, game->player.sprite.img_ptr,
		game->player.pos.x * game->player.sprite.size.x,
		game->player.pos.y * game->player.sprite.size.y);
}
