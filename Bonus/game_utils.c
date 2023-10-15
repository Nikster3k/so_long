/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 19:41:48 by nsassenb          #+#    #+#             */
/*   Updated: 2023/10/15 19:25:20 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_keyhook(int keycode, t_game *game)
{
	int	success;

	if (keycode == KEY_ESCAPE)
		mlx_loop_end(game->mlx_ptr);
	if (keycode == KEY_W)
		success = ft_check_player_move(game, (t_point){0, -1});
	if (keycode == KEY_S)
		success = ft_check_player_move(game, (t_point){0, 1});
	if (keycode == KEY_D)
		success = ft_check_player_move(game, (t_point){1, 0});
	if (keycode == KEY_A)
		success = ft_check_player_move(game, (t_point){-1, 0});
	if (success)
		ft_move_enemies(game);
	ft_draw_player(game);
	return (0);
}

void	ft_initialize_func_hooks(t_game *game)
{
	mlx_hook(game->win_ptr, 17, 0, mlx_loop_end, game->mlx_ptr);
	mlx_loop_hook(game->mlx_ptr, ft_update_animations, &game->animator);
	mlx_key_hook(game->win_ptr, ft_keyhook, game);
}

int	ft_destroy_game(t_game *game, int err)
{
	ft_free_map(&game->map);
	if (game->mlx_ptr != NULL)
	{
		if (game->coin.img_ptr != NULL)
			mlx_destroy_image(game->mlx_ptr, game->coin.img_ptr);
		if (game->ground.img_ptr != NULL)
			mlx_destroy_image(game->mlx_ptr, game->ground.img_ptr);
		if (game->wall.img_ptr != NULL)
			mlx_destroy_image(game->mlx_ptr, game->wall.img_ptr);
		if (game->exit.img_ptr != NULL)
			mlx_destroy_image(game->mlx_ptr, game->exit.img_ptr);
		if (game->player.ent.sprite.imgs != NULL)
			ft_destroy_animation(game->mlx_ptr, &game->player.ent.sprite);
	}
	if (game->mlx_ptr != NULL && game->win_ptr != NULL)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->mlx_ptr != NULL)
		mlx_destroy_display(game->mlx_ptr);
	free(game->mlx_ptr);
	free(game->enems);
	return (ft_print_error(err));
}
