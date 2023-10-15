/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:34:14 by nsassenb          #+#    #+#             */
/*   Updated: 2023/10/12 18:18:17 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_initialize_images(t_game *game)
{
	int	size;

	size = IMG_SIZE;
	game->player.ent.sprite.img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			"textures/Knight1.xpm",
			&size,
			&size);
	game->player.ent.pos = game->map.pstart;
	game->wall.img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			"textures/wall.xpm", &size, &size);
	game->coin.img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			"textures/coin.xpm", &size, &size);
	game->ground.img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			"textures/ground.xpm", &size, &size);
	game->exit.img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			"textures/Exit.xpm", &size, &size);
	return (!game->coin.img_ptr || !game->wall.img_ptr
		|| !game->ground.img_ptr || !game->exit.img_ptr
		|| !game->player.ent.sprite.img_ptr);
}
