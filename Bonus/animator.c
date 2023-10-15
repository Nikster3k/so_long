/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 19:07:39 by nsassenb          #+#    #+#             */
/*   Updated: 2023/10/15 19:27:24 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_update_animations(t_animator *animator)
{
	static int	i = 0;
	t_list		*current;
	t_anim		*animdata;

	current = animator->anims;
	while (current != NULL)
	{
		if (i % 10000)
		{
			animdata = current->content;
			if (animdata->current < animdata->animlen)
				animdata->current++;
			else
				animdata->current = 0;
			ft_printf("Updated animation current to %i\n", animdata->current);
			current = current->next;
		}
		i++;
	}
	return (SUCCESS);
}