/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fts_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:08:47 by nsassenb          #+#    #+#             */
/*   Updated: 2023/10/17 15:59:33 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	ft_draw_map(t_game *game)
{
	t_point	iter;

	iter = (t_point){0, 0};
	while (iter.y < game->map.size.y)
	{
		iter.x = 0;
		while (iter.x < game->map.size.x)
		{
			ft_draw_at(game, iter);
			iter.x++;
		}
		iter.y++;
	}
}

void	ft_draw_at(t_game *game, t_point pos)
{
	char	tile;

	tile = ft_map_getat(&game->map, pos);
	if (tile == WALL)
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->wall.img_ptr, pos.x * IMG_SIZE, pos.y * IMG_SIZE);
	else if (tile == COLLECTABLE)
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->coin.img_ptr, pos.x * IMG_SIZE, pos.y * IMG_SIZE);
	else if (tile == EXIT)
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->exit.img_ptr, pos.x * IMG_SIZE, pos.y * IMG_SIZE);
	else
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->ground.img_ptr, pos.x * IMG_SIZE, pos.y * IMG_SIZE);
}

void	ft_draw_player(t_game *game)
{
	mlx_put_image_to_window(
		game->mlx_ptr, game->win_ptr,
		game->player.ent.sprite
		.imgs[(int)game->player.ent.sprite.current].img_ptr,
		game->player.ent.pos.x * IMG_SIZE,
		game->player.ent.pos.y * IMG_SIZE);
}

void	ft_draw_string(t_game *game)
{
	char	*joined;
	char	*number;
	int		x;

	x = game->map.size.x / 2;
	while (x < game->map.size.x)
		ft_draw_at(game, (t_point){x++, game->map.size.y});
	number = ft_itoa(game->player.moves);
	joined = ft_strjoin("Moves: ", number);
	mlx_string_put(game->mlx_ptr, game->win_ptr,
		game->win_size.x / 2,
		game->win_size.y - 1, 0xFFFFFFFF, joined);
	free(number);
	free(joined);
}

void	ft_draw_all(t_game *game)
{
	ft_draw_map(game);
	ft_draw_enemies(game);
	ft_draw_player(game);
}
