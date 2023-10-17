/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:13:12 by nsassenb          #+#    #+#             */
/*   Updated: 2023/10/17 15:59:33 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

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

void	ft_kill_all(t_game *game)
{
	t_list	*newlst;
	t_list	*current;
	t_anim	*animdata;

	current = game->animator.anims;
	newlst = NULL;
	while (current != NULL)
	{
		animdata = current->content;
		if (animdata->imgs != game->enem_anim.imgs)
			ft_lstadd_front(&newlst, ft_lstnew(current->content));
		current = current->next;
	}
	ft_lstclear(&game->animator.anims, ft_empty_func);
	game->animator.anims = newlst;
	ft_bzero(game->enems, sizeof(t_enemy) * game->map.gcount);
	free(game->enems);
	game->enems = NULL;
	game->map.gcount = 0;
}
