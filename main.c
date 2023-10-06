/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:54:08 by nsassenb          #+#    #+#             */
/*   Updated: 2023/10/06 13:08:35 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "so_long.h"
#include <stdlib.h>
#include <stdio.h>

int	testHook(void)
{
	printf("hello world");
	return (1);
}

int	main(void)
{
	void	*init;
	void	*window;

	t_map map = read_map("testmap.ber");
	if (map.map == NULL)
		printf("Error in readmap\n");
	return (0);
	init = mlx_init();
	if (init == NULL)
		return (-1);
	window = mlx_new_window(init, 640, 360, "Hello World");
	if (window == NULL)
	{
		mlx_destroy_display(init);
		return (-2);
	}
	int out = mlx_key_hook(init, &testHook, NULL);
	printf("%i", out);
	mlx_loop(init);

	mlx_destroy_window(init, window);
	mlx_destroy_display(init);
}