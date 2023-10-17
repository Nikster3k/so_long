/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animator_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 19:07:39 by nsassenb          #+#    #+#             */
/*   Updated: 2023/10/17 15:59:31 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	ft_update_animations(t_animator *animator, float delta)
{
	t_list				*current;
	t_anim				*animdata;

	current = animator->anims;
	while (current != NULL)
	{
		animdata = current->content;
		if (animdata->animlen != 0 || animdata->imgs != NULL)
		{
			if (animdata->current + delta < animdata->animlen)
				animdata->current += delta;
			else
				animdata->current = 0;
		}
		current = current->next;
	}
	return (SUCCESS);
}
