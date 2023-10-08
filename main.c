/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:54:08 by nsassenb          #+#    #+#             */
/*   Updated: 2023/10/08 22:04:11 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "so_long.h"
#include <stdlib.h>
#include <stdio.h>

int	testHook(int t)
{
	printf("%s, %i", "hello world", t);
	return (1);
}

int	main(void)
{
	void	*init;
	void	*window;
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!ft_read_map(map, "testmap.ber"))
		printf("failed map read");
	
	for (size_t i = 0; i < map->mlist.size - 1; i++)
	{
		printf("%s\n", map->mlist.data[i]);
	}
	ft_fullfree_ml(&map->mlist);
	free(map);

	init = mlx_init();
	if (init == NULL)
		return (-1);
	window = mlx_new_window(init, 640, 360, "Hello World");
	if (window == NULL)
	{
		mlx_destroy_display(init);
		return (-2);
	}
	int	test = 5;
	//int out = mlx_key_hook(init, &testHook, &test);
	//printf("%i", out);
	mlx_loop_hook(init, &testHook, 30052002);
	//mlx_hook(init, )
	mlx_loop(init);

	mlx_destroy_window(init, window);
	mlx_destroy_display(init);
}