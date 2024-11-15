/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:34:14 by nsassenb          #+#    #+#             */
/*   Updated: 2023/10/17 18:06:18 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

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
	ft_load_anim(game, &game->player.ent.sprite, "textures/Knight/",
		(char *[]){"Knight1.xpm", "Knight2.xpm", "Knight3.xpm",
		"Knight4.xpm", "Knight5.xpm", "Knight6.xpm", "Knight7.xpm",
		"Knight8.xpm", NULL});
	if (game->map.gcount > 0)
		ft_load_anim(game, &game->enem_anim, "textures/Monster/",
			(char *[]){"IdleTile1.xpm", "IdleTile2.xpm",
			"IdleTile3.xpm", "IdleTile4.xpm", NULL});
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
		|| !game->player.ent.sprite.imgs
		|| (!game->enem_anim.imgs && game->enem_anim.animlen != 0));
}

void	ft_swap_img(void *mlx_ptr, t_image *img, char *path)
{
	void	*imgtmp;

	imgtmp = img->img_ptr;
	img->img_ptr = ft_load_image(mlx_ptr, path);
	if (img->img_ptr == NULL)
		img->img_ptr = imgtmp;
	else
		mlx_destroy_image(mlx_ptr, imgtmp);
}
