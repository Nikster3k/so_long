/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 19:07:39 by nsassenb          #+#    #+#             */
/*   Updated: 2023/10/15 19:47:43 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_update_animations(t_animator *animator)
{
	static unsigned int	i = 0;
	t_list				*current;
	t_anim				*animdata;

	current = animator->anims;
	while (current != NULL)
	{
		if (i % 100000000 == 0)
		{
			animdata = current->content;
			if (animdata->current < animdata->animlen - 1)
				animdata->current++;
			else
				animdata->current = 0;
			current = current->next;
		}
		i++;
	}
	return (SUCCESS);
}