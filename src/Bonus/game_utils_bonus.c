/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 19:41:48 by nsassenb          #+#    #+#             */
/*   Updated: 2023/10/17 20:41:59 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"
#include <time.h>

int	ft_keyhook(int keycode, t_game *game)
{
	int	success;

	success = 0;
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
		ft_draw_string(game);
	return (0);
}

static int	ft_loop_update(t_game *game)
{
	static double	deltatime = 0;
	struct timespec	start;
	struct timespec	end;
	int				err;

	clock_gettime(CLOCK_REALTIME, &start);
	ft_move_enemies(game, deltatime);
	err = ft_update_animations(&game->animator, deltatime * 4);
	ft_draw_player(game);
	if (ft_collision_check(&game->player, game->enems, game->map.gcount))
		ft_on_enemycollision(game);
	clock_gettime(CLOCK_REALTIME, &end);
	deltatime = (end.tv_sec - start.tv_sec) * 1e6;
	deltatime += (end.tv_nsec - start.tv_nsec) / 1e6;
	return (err);
}

void	ft_initialize_func_hooks(t_game *game)
{
	mlx_hook(game->win_ptr, 17, 0, mlx_loop_end, game->mlx_ptr);
	mlx_loop_hook(game->mlx_ptr, ft_loop_update, game);
	mlx_key_hook(game->win_ptr, ft_keyhook, game);
}

void	ft_empty_func(void *nothing)
{
	(void)nothing;
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
		if (game->enem_anim.imgs != NULL)
			ft_destroy_animation(game->mlx_ptr, &game->enem_anim);
	}
	if (game->mlx_ptr != NULL && game->win_ptr != NULL)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->mlx_ptr != NULL)
		mlx_destroy_display(game->mlx_ptr);
	free(game->mlx_ptr);
	free(game->enems);
	ft_lstclear(&game->animator.anims, ft_empty_func);
	return (ft_print_error(err));
}
