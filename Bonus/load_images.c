/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:34:14 by nsassenb          #+#    #+#             */
/*   Updated: 2023/10/15 18:47:05 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	*ft_load_image(void *mlx_ptr, char *filepath)
{
	int	size;

	size = IMG_SIZE;
	return (mlx_xpm_file_to_image(mlx_ptr, filepath, &size, &size));
}

int	ft_initialize_images(t_game *game)
{
	int	size;

	size = IMG_SIZE;
	ft_load_anim(game, &game->player.ent.sprite, "textures/Monster/",
		(char *[]){"IdleTile1.xpm", "IdleTile2.xpm", NULL});
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
		|| !game->player.ent.sprite.imgs);
}
