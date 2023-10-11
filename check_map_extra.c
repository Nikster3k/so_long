/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_extra.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 12:46:20 by nsassenb          #+#    #+#             */
/*   Updated: 2023/10/11 14:34:48 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_check_for_leaks(t_map *filled)
{
	char	*found;
	int		y;

	y = 1;
	found = ft_strchr(filled->lines[0], 'F');
	if (found != NULL)
		return (INVALID_MAP);
	found = ft_strchr(filled->lines[filled->size.y - 1], 'F');
	if (found != NULL)
		return (INVALID_MAP);
	while (y < filled->size.y - 2)
	{
		if (filled->lines[y][0] == 'F')
			return (INVALID_MAP);
		if (filled->lines[y][filled->size.x - 1] == 'F')
			return (INVALID_MAP);
		y++;
	}
	return (SUCCESS);
}