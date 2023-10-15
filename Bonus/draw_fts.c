/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:08:47 by nsassenb          #+#    #+#             */
/*   Updated: 2023/10/15 18:38:15 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_swap_img(void *mlx_ptr, t_image *img, char *path)
{
	int		size;
	void	*imgtmp;

	size = IMG_SIZE;
	imgtmp = img->img_ptr;
	img->img_ptr = mlx_xpm_file_to_image(mlx_ptr,
			path, &size, &size);
	if (img->img_ptr == NULL)
		img->img_ptr = imgtmp;
	else
		mlx_destroy_image(mlx_ptr, imgtmp);
}

void	ft_draw_map(t_game *game)
{
	t_point	iter;

	iter = (t_point){0, 0};
	while (iter.y < game->map.size.y)
	{
		iter.x = 0;
		while (iter.x < game->map.size.x)
		{
			ft_draw_at(game, iter);
			iter.x++;
		}
		iter.y++;
	}
}

void	ft_draw_at(t_game *game, t_point pos)
{
	char	tile;

	tile = ft_map_getat(&game->map, pos);
	if (tile == WALL)
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->wall.img_ptr, pos.x * IMG_SIZE, pos.y * IMG_SIZE);
	else if (tile == COLLECTABLE)
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->coin.img_ptr, pos.x * IMG_SIZE, pos.y * IMG_SIZE);
	else if (tile == EXIT)
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->exit.img_ptr, pos.x * IMG_SIZE, pos.y * IMG_SIZE);
	else
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->ground.img_ptr, pos.x * IMG_SIZE, pos.y * IMG_SIZE);
}

void	ft_draw_player(t_game *game)
{
	mlx_put_image_to_window(
		game->mlx_ptr, game->win_ptr,
		game->player.ent.sprite.imgs[game->player.ent.sprite.current].img_ptr,
		game->player.ent.pos.x * IMG_SIZE,
		game->player.ent.pos.y * IMG_SIZE);
}

void	ft_draw_all(t_game *game)
{
	ft_draw_map(game);
	ft_draw_player(game);
}
