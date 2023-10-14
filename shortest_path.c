/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shortest_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 18:41:51 by nsassenb          #+#    #+#             */
/*   Updated: 2023/10/14 18:55:08 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_pos_isvalid(t_map *map, t_point pos)
{
	char	a;

	a = ft_map_getat(map, pos);
	if (a == '\0' || a == '1' || a == 'X')
		return (0);
	return (1);
}

static void	ft_check_all_dirs(t_map *copy, t_path *current, t_vector *queue)
{
	static t_point	dirs[] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
	int				i;
	t_point			newpos;

	i = 0;
	while (i < 4)
	{
		newpos = (t_point)
		{current->pos.x + dirs[i].x, current->pos.y + dirs[i].y};
		if (ft_pos_isvalid(copy, newpos))
		{
			ft_vector_add(queue, (t_path){newpos, current->distance + 1});
			copy->lines[newpos.y][newpos.x] = 'X';
		}
		i++;
	}
}

int	ft_shortest_moves(t_map *map, t_point start, t_point goal)
{
	t_vector		queue;
	t_map			copy;
	t_path			current;

	queue = (t_vector){NULL, 0, 0};
	if (ft_clone_map(map, &copy))
		return (-1);
	current.pos = start;
	current.distance = 0;
	ft_vector_add(&queue, current);
	copy.lines[start.y][start.x] = 'X';
	while (queue.size)
	{
		current = ft_vector_pop(&queue);
		if (current.pos.x == goal.x && current.pos.y == goal.y)
		{
			ft_vector_clear(&queue);
			ft_free_map(&copy);
			return (current.distance);
		}
		ft_check_all_dirs(&copy, &current, &queue);
	}
	ft_vector_clear(&queue);
	ft_free_map(&copy);
	return (-1);
}
