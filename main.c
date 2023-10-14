/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:54:08 by nsassenb          #+#    #+#             */
/*   Updated: 2023/10/14 19:45:20 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	ft_initialize_func_hooks(&game);
	ft_draw_all(&game);
	mlx_loop(game.mlx_ptr);
	return (ft_destroy_game(&game, err));
}
