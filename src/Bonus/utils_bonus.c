/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 19:33:03 by nsassenb          #+#    #+#             */
/*   Updated: 2023/10/17 20:38:54 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	ft_safestrlen(const char *s)
{
	int	count;

	count = 0;
	if (s == NULL)
		return (count);
	while (s[count])
		count++;
	return (count);
}

void	ft_draw_block(t_game *game, t_point start, int sizex, int sizey)
{
	int	x;
	int	y;

	y = 0;
	while (y < sizey)
	{
		x = 0;
		while (x < sizex)
		{
			mlx_pixel_put(
				game->mlx_ptr, game->win_ptr,
				start.x + x, start.y + y, 0x222222);
			x++;
		}
		y++;
	}
}
