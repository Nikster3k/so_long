/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:54:08 by nsassenb          #+#    #+#             */
/*   Updated: 2023/10/12 19:44:56 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_keyhook(int keycode, t_game *game)
{
	if (keycode == KEY_ESCAPE)
		mlx_loop_end(game->mlx_ptr);
	if (keycode == KEY_W)
		ft_check_player_move(game, (t_point){0, -1});
	if (keycode == KEY_S)
		ft_check_player_move(game, (t_point){0, 1});
	if (keycode == KEY_D)
		ft_check_player_move(game, (t_point){1, 0});
	if (keycode == KEY_A)
		ft_check_player_move(game, (t_point){-1, 0});
	ft_draw_player(game);
	return (0);
}

void	ft_initalize_func_hooks(t_game *game)
{
	mlx_hook(game->win_ptr, 17, 0, mlx_loop_end, game->mlx_ptr);
	mlx_key_hook(game->win_ptr, ft_keyhook, game);
	ft_draw_map(game);
	ft_draw_player(game);
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
		if (game->player.ent.sprite.img_ptr != NULL)
			mlx_destroy_image(game->mlx_ptr, game->player.ent.sprite.img_ptr);
	}
	if (game->mlx_ptr != NULL && game->win_ptr != NULL)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->mlx_ptr != NULL)
		mlx_destroy_display(game->mlx_ptr);
	free(game->mlx_ptr);
	return (ft_print_error(err));
}

static void	ft_initialize_game(t_game *game)
{
	game->mlx_ptr = NULL;
	game->win_ptr = NULL;
	game->player.collected = 0;
	game->player.moves = 0;
}

int	main(int argc, char **argv)
{
	t_game	game;
	int		err;

	err = SUCCESS;
	if (argc != 2)
		return (ft_print_error(NO_FILE));
	err = ft_create_map(&game.map, argv[1]);
	if (err)
		return (ft_print_error(err));
	ft_initialize_game(&game);
	game.mlx_ptr = mlx_init();
	if (game.mlx_ptr == NULL)
		return (ft_destroy_game(&game, 1));
	if (ft_initialize_images(&game))
		return (ft_destroy_game(&game, 1));
	game.win_ptr = mlx_new_window(game.mlx_ptr,
			game.map.size.x * IMG_SIZE,
			game.map.size.y * IMG_SIZE,
			argv[0]);
	if (game.win_ptr == NULL)
		return (ft_destroy_game(&game, 1));
	ft_initalize_func_hooks(&game);
	mlx_loop(game.mlx_ptr);
	return (ft_destroy_game(&game, err));
}
