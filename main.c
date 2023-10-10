/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:54:08 by nsassenb          #+#    #+#             */
/*   Updated: 2023/10/10 18:03:49 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_clear_window(t_game *game)
{
	ft_printf("CLEAR\n");
	return (mlx_clear_window(game->mlx_ptr, game->win_ptr));
}

int	ft_keyhook(int keycode, t_game *game)
{
	if (keycode == ESCAPE_KEY)
		mlx_loop_end(game->mlx_ptr);
	if (keycode == 119)
		game->player.pos.y -= 1;
	if (keycode == 115)
		game->player.pos.y += 1;
	if (keycode == 100)
		game->player.pos.x += 1;
	if (keycode == 97)
		game->player.pos.x -= 1;
	if (keycode == SPACE_KEY)
		mlx_string_put(
			game->mlx_ptr, game->win_ptr, 0, 50, 0xffffffff, "Hello world");
	if (keycode == L_CONTROL_KEY)
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
		game->mlx_ptr, game->win_ptr,
		game->player.sprite.img_ptr,
		game->player.pos.x * game->player.sprite.size.x,
		game->player.pos.y * game->player.sprite.size.y);
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
	mlx_loop_hook(game.mlx_ptr, draw_all, &game);
	mlx_key_hook(game.win_ptr, ft_keyhook, &game);
	mlx_loop(game.mlx_ptr);
	mlx_destroy_window(game.mlx_ptr, game.win_ptr);
	mlx_destroy_display(game.mlx_ptr);
}
