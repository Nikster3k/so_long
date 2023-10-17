/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 17:07:54 by nsassenb          #+#    #+#             */
/*   Updated: 2023/10/17 17:08:15 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	ft_initialize_enemies(t_game *game)
{
	t_point	pos;
	int		i;

	game->enems = ft_calloc(sizeof(t_enemy), game->map.gcount);
	if (game->enems == NULL)
		return (MALLOC_FAIL);
	i = 0;
	while (i < game->map.gcount)
	{
		pos = ft_getposof(&game->map, 'G');
		game->enems[i].base.pos = pos;
		game->enems[i].x = pos.x;
		game->enems[i].y = pos.y;
		game->map.lines[pos.y][pos.x] = '0';
		game->enems[i].movdir = (t_point){1, 0};
		game->enems[i].base.sprite = game->enem_anim;
		game->enems[i].base.sprite.current = i % game->enem_anim.animlen;
		ft_lstadd_front(&game->animator.anims,
			ft_lstnew(&game->enems[i].base.sprite));
		i++;
	}
	return (SUCCESS);
}

void	ft_draw_enemy(t_game *game, t_enemy *enem)
{
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
		enem->base.sprite.imgs[(int)enem->base.sprite.current].img_ptr,
		enem->base.pos.x * IMG_SIZE, enem->base.pos.y * IMG_SIZE);
}

void	ft_draw_enemies(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.gcount)
		ft_draw_enemy(game, &game->enems[i++]);
}

static void	ft_update_enem_pos(t_game *game, t_enemy *enem, float delta)
{
	enem->x += enem->movdir.x * delta;
	enem->y += enem->movdir.y * delta;
	if ((int)enem->y != enem->base.pos.y || (int)enem->x != enem->base.pos.x)
	{
		ft_draw_at(game, enem->base.pos);
		enem->base.pos.x = (int)enem->x;
		enem->base.pos.y = (int)enem->y;
	}
}

void	ft_move_enemies(t_game *game, float delta)
{
	t_enemy	*enems;
	char	newpos;
	int		i;

	i = 0;
	enems = game->enems;
	while (i < game->map.gcount)
	{
		newpos = ft_map_getat(&game->map, (t_point){(int)(enems[i].x
					+ enems[i].movdir.x * delta), (int)(enems[i].y
					+ enems[i].movdir.y * delta)});
		if (newpos != 0)
		{
			if (newpos == '1')
				enems[i].movdir = (t_point){enems[i].movdir.x * -1,
					enems[i].movdir.y * -1};
			ft_update_enem_pos(game, &enems[i], delta);
		}
		i++;
	}
	ft_draw_enemies(game);
}
