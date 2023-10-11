/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:54:08 by nsassenb          #+#    #+#             */
/*   Updated: 2023/10/11 14:33:52 by nsassenb         ###   ########.fr       */
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
	if (count % 1000 == 0)
		ft_printf("Frame: %i\n", count);
	count++;
	return (SUCCESS);
}

int	ft_keyhook(int keycode, t_game *game)
{
	if (keycode == KEY_ESCAPE)
		mlx_loop_end(game->mlx_ptr);
	if (keycode == KEY_W)
		ft_check_player_move(&game->player, &game->map, (t_point){0, -1});
	if (keycode == KEY_S)
		ft_check_player_move(&game->player, &game->map, (t_point){0, 1});
	if (keycode == KEY_D)
		ft_check_player_move(&game->player, &game->map, (t_point){1, 0});
	if (keycode == 97)
		ft_check_player_move(&game->player, &game->map, (t_point){-1, 0});
	if (keycode == KEY_A)
		mlx_string_put(
			game->mlx_ptr, game->win_ptr, 0, 50, 0xffffffff, "Hello world");
	if (keycode == KEY_L_CONTROL)
		ft_clear_window(game);
	ft_printf("Keycode: %i c: %c\n", keycode, keycode);
	return (0);
}

int	draw_all(t_game *game)
{
	for (size_t y = 0; y < game->map.size.y; y++)
	{
		for (size_t x = 0; x < game->map.size.x; x++)
		{
			if (game->map.lines[y][x] == '1')
			{
				mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->wall.img_ptr, x * game->wall.size.x, y * game->wall.size.y);
				continue ;
			}
			mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->ground.img_ptr, x * game->ground.size.x, y * game->ground.size.y);
		}
	}
	mlx_put_image_to_window(
		game->mlx_ptr, game->win_ptr, game->player.sprite.img_ptr,
		game->player.pos.x * game->player.sprite.size.x,
		game->player.pos.y * game->player.sprite.size.y);
	framecount();
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_game	game;
	char	*filepath;
	int		err;

	if (argc != 2)
		return (-1);
	filepath = ft_strjoin("maps/", argv[1]);
	ft_create_map(&game.map, filepath);
	free(filepath);
	game.mlx_ptr = mlx_init();
	if (game.mlx_ptr == NULL)
		return (1);
	game.player.sprite.size = (t_point){32, 32};
	game.player.sprite.img_ptr = mlx_xpm_file_to_image(game.mlx_ptr,
			"textures/Knight1.xpm",
			&game.player.sprite.size.x,
			&game.player.sprite.size.y);
	game.wall.size = (t_point){32, 32};
	game.wall.img_ptr = mlx_xpm_file_to_image(game.mlx_ptr,
			"textures/wall.xpm", &game.wall.size.x, &game.wall.size.y);
	game.ground.size = (t_point){32, 32};
	game.ground.img_ptr = mlx_xpm_file_to_image(game.mlx_ptr,
			"textures/ground.xpm", &game.ground.size.x, &game.ground.size.y);
	game.win_ptr = mlx_new_window(game.mlx_ptr,
			game.map.size.x * game.ground.size.x,
			game.map.size.y * game.ground.size.y,
			argv[0]);
	if (game.win_ptr == NULL)
	{
		mlx_destroy_display(game.mlx_ptr);
		return (-1);
	}
	game.player.pos = game.map.pstart;
	mlx_hook(game.win_ptr, 17, 0, mlx_loop_end, game.mlx_ptr);
	mlx_loop_hook(game.mlx_ptr, draw_all, &game);
	mlx_key_hook(game.win_ptr, ft_keyhook, &game);
	mlx_loop(game.mlx_ptr);

	ft_free_map(&game.map);
	mlx_destroy_image(game.mlx_ptr, game.ground.img_ptr);
	mlx_destroy_image(game.mlx_ptr, game.wall.img_ptr);
	mlx_destroy_image(game.mlx_ptr, game.player.sprite.img_ptr);
	mlx_destroy_window(game.mlx_ptr, game.win_ptr);
	mlx_destroy_display(game.mlx_ptr);
	free(game.mlx_ptr);
}
