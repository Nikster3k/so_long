/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:54:08 by nsassenb          #+#    #+#             */
/*   Updated: 2023/10/09 16:46:28 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

typedef struct s_game
{
	void	*mlx_ptr;
	void	*win_ptr;
}	t_game;

int	clearwin(t_game *game)
{
	return (mlx_clear_window(game->mlx_ptr, game->win_ptr));
}

int	testhook(int keycode, t_game *game)
{
	if (keycode == ESCAPE_KEY)
		mlx_loop_end(game->mlx_ptr);
	if (keycode == SPACE_KEY)
		mlx_string_put(game->mlx_ptr, game->win_ptr, 0, 50, 0xffffffff, "Hello world");
	if (keycode == L_CONTROL_KEY)
		clearwin(game);
	ft_printf("Keycode: %i c: %c\n", keycode, keycode);
	return (0);
}

int	main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*imgptr;
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!ft_read_map(map, "maps/testmap.ber"))
		ft_printf("failed map read");
	for (size_t i = 0; i < map->size.y; i++)
		ft_printf("%s\n", map->lines[i]);
	if (ft_check_map(map))
		ft_printf("%s\n", "Invalid map?");
	for (size_t i = 0; i < map->size.y; i++)
		ft_printf("%s\n", map->lines[i]);
	mlx_ptr = mlx_init();
	if (mlx_ptr == NULL)
		return (-1);
	win_ptr = mlx_new_window(mlx_ptr, 640, 360, "Hello World");
	if (win_ptr == NULL)
	{
		mlx_destroy_display(mlx_ptr);
		return (-2);
	}
	mlx_key_hook(win_ptr, testhook, &(t_game){mlx_ptr, win_ptr});
	imgptr = mlx_new_image(mlx_ptr, 32, 32);
	if (imgptr == NULL)
	{
		mlx_destroy_window(mlx_ptr, win_ptr);
		mlx_destroy_display(mlx_ptr);
		return (-3);
	}
	int x = 32;
	imgptr = mlx_xpm_file_to_image(mlx_ptr, "textures/Knight1.xpm", &x, &x);
	mlx_put_image_to_window(mlx_ptr, win_ptr, imgptr, 0, 80);
	mlx_loop(mlx_ptr);
	mlx_destroy_image(mlx_ptr, imgptr);
	mlx_destroy_window(mlx_ptr, win_ptr);
	mlx_destroy_display(mlx_ptr);
}