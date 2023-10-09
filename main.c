/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:54:08 by nsassenb          #+#    #+#             */
/*   Updated: 2023/10/09 12:15:25 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>

int	testhook(int keycode, void *mlx_ptr)
{
	if (keycode == ESCAPE_KEY)
		mlx_loop_end(mlx_ptr);
	return (1);
}

int	destroy(void *mlx_ptr)
{
	static int	i = 0;

	if (i > 1000000)
		mlx_loop_end(mlx_ptr);
	printf("%i\n", i);
	i++;
	return (0);
}

int	main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!ft_read_map(map, "testmap.ber"))
		printf("failed map read");
	for (size_t i = 0; i < map->mlist.size - 1; i++)
		printf("%s\n", map->mlist.data[i]);
	ft_fullfree_ml(&map->mlist);
	free(map);
	mlx_ptr = mlx_init();
	if (mlx_ptr == NULL)
		return (-1);
	win_ptr = mlx_new_window(mlx_ptr, 640, 360, "Hello World");
	if (win_ptr == NULL)
	{
		mlx_destroy_display(mlx_ptr);
		return (-2);
	}
	mlx_key_hook(win_ptr, testhook, NULL);
	mlx_loop_hook(mlx_ptr, destroy, mlx_ptr);
	mlx_loop(mlx_ptr);
	mlx_destroy_window(mlx_ptr, win_ptr);
	mlx_destroy_display(mlx_ptr);
}