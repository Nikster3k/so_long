/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:54:08 by nsassenb          #+#    #+#             */
/*   Updated: 2023/10/12 13:08:28 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_clear_window(t_game *game)
{
	ft_printf("CLEAR\n");
	return (mlx_clear_window(game->mlx_ptr, game->win_ptr));
}

int	framecount(void)
{
	static int	count = 0;
	// else if (count % 1000 == 0)
	// 	ft_printf("Frame: %i\n", count);
	count++;
	return (SUCCESS);
}

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
	if (keycode == KEY_SPACE)
		mlx_string_put(
			game->mlx_ptr, game->win_ptr, 0, 50, 0xffffffff, "Hello world");
	if (keycode == KEY_L_CONTROL)
		ft_clear_window(game);
	ft_draw_player(game);
	return (0);
}

void	ft_initialize_images(t_game *game)
{
	game->player.sprite.size = (t_point){32, 32};
	game->player.sprite.img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			"textures/Knight1.xpm",
			&game->player.sprite.size.x,
			&game->player.sprite.size.y);
	game->player.collected = 0;
	game->wall.size = (t_point){32, 32};
	game->wall.img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			"textures/wall.xpm", &game->wall.size.x, &game->wall.size.y);
	game->coin.size = (t_point){32, 32};
	game->coin.img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			"textures/coin.xpm", &game->coin.size.x, &game->coin.size.y);
	game->ground.size = (t_point){32, 32};
	game->ground.img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			"textures/ground.xpm", &game->ground.size.x, &game->ground.size.y);
	game->player.pos = game->map.pstart;
}

void	ft_initalize_func_hooks(t_game *game)
{
	mlx_hook(game->win_ptr, 17, 0, mlx_loop_end, game->mlx_ptr);
	mlx_loop_hook(game->mlx_ptr, framecount, NULL);
	mlx_key_hook(game->win_ptr, ft_keyhook, game);
	ft_draw_map(game);
	ft_draw_player(game);
}

static int	ft_destroy_game(t_game *game, int err)
{
	ft_free_map(&game->map);
	mlx_destroy_image(game->mlx_ptr, game->coin.img_ptr);
	mlx_destroy_image(game->mlx_ptr, game->ground.img_ptr);
	mlx_destroy_image(game->mlx_ptr, game->wall.img_ptr);
	mlx_destroy_image(game->mlx_ptr, game->player.sprite.img_ptr);
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	mlx_destroy_display(game->mlx_ptr);
	free(game->mlx_ptr);
	return (ft_print_error(err));
}

int	main(int argc, char **argv)
{
	t_game	game;
	int		err;

	if (argc != 2)
		return (-1);
	err = ft_create_map(&game.map, argv[1]);
	if (err)
		return (ft_print_error(err));
	game.mlx_ptr = mlx_init();
	if (game.mlx_ptr == NULL)
		return (ft_destroy_game(&game, 1));
	ft_initialize_images(&game);
	game.win_ptr = mlx_new_window(game.mlx_ptr,
			game.map.size.x * game.ground.size.x,
			game.map.size.y * game.ground.size.y,
			argv[0]);
	if (game.win_ptr == NULL)
		return (ft_destroy_game(&game, 1));
	ft_initalize_func_hooks(&game);
	mlx_loop(game.mlx_ptr);
	ft_destroy_game(&game, err);
}
