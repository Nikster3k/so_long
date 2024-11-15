/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:54:08 by nsassenb          #+#    #+#             */
/*   Updated: 2023/10/17 15:59:33 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static int	ft_initialize_stuff(t_game *game)
{
	game->win_size = (t_point){game->map.size.x * IMG_SIZE,
		game->map.size.y * IMG_SIZE};
	return (ft_initialize_images(game) || ft_initialize_enemies(game));
}

int	main(int argc, char **argv)
{
	t_game	game;
	int		err;

	err = SUCCESS;
	if (argc != 2)
		return (ft_print_error(NO_FILE));
	ft_bzero(&game, sizeof(t_game));
	err = ft_create_map(&game.map, argv[1]);
	if (err)
		return (ft_print_error(err));
	game.mlx_ptr = mlx_init();
	if (game.mlx_ptr == NULL)
		return (ft_destroy_game(&game, 1));
	if (ft_initialize_stuff(&game))
		return (ft_destroy_game(&game, MALLOC_FAIL));
	game.win_ptr = mlx_new_window(game.mlx_ptr,
			game.win_size.x,
			game.win_size.y,
			argv[0]);
	if (game.win_ptr == NULL)
		return (ft_destroy_game(&game, 1));
	ft_initialize_func_hooks(&game);
	ft_draw_all(&game);
	mlx_loop(game.mlx_ptr);
	return (ft_destroy_game(&game, err));
}
