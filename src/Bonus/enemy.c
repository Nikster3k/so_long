/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 17:07:54 by nsassenb          #+#    #+#             */
/*   Updated: 2023/10/16 19:46:50 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_collision_check(t_player *player, t_enemy *enemies, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (player->ent.pos.x == enemies[i].base.pos.x
			&& player->ent.pos.y == enemies[i].base.pos.y)
			return (1);
		i++;
	}
	return (0);
}

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
	mlx_put_image_to_window(
		game->mlx_ptr, game->win_ptr,
		enem->base.sprite.imgs[(int)enem->base.sprite.current].img_ptr,
		enem->base.pos.x * IMG_SIZE,
		enem->base.pos.y * IMG_SIZE);
}

void	ft_draw_enemies(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.gcount)
		ft_draw_enemy(game, &game->enems[i++]);
}

void	ft_move_enemies(t_game *game)
{
	t_enemy	*enems;
	char	newpos;
	int		i;

	i = 0;
	enems = game->enems;
	while (i < game->map.gcount)
	{
		newpos = ft_map_getat(
				&game->map, (t_point){
				enems[i].base.pos.x + enems[i].movdir.x,
				enems[i].base.pos.y + enems[i].movdir.y});
		if (newpos != 0)
		{
			if (newpos == '1')
				enems[i].movdir = (t_point){
					enems[i].movdir.x * -1, enems[i].movdir.y * -1};
			ft_draw_at(game, enems[i].base.pos);
			ft_move_entity(&enems[i].base, enems[i].movdir);
		}
		i++;
	}
}
