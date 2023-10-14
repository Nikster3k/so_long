/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 18:41:51 by nsassenb          #+#    #+#             */
/*   Updated: 2023/10/14 18:57:07 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "so_long.h"

// int	abs(int x)
// {
// 	if (x < 0)
// 		return (-x);
// 	return (x);
// }

// void	*ft_lstfind(t_list **lst, void *data, size_t size)
// {
// 	t_list	*current;

// 	current = *lst;
// 	while (current != NULL)
// 	{
// 		if (ft_memcmp(current->content, data, size))
// 			return (current->content);
// 		current = current->next;
// 	}
// 	return (NULL);
// }

// int	ft_manhattan_dist(t_point lhs, t_point rhs)
// {
// 	return (abs((lhs.x - rhs.x) + (lhs.y - rhs.x)));
// }

// void	*ft_lstpop(t_list **list)
// {
// 	t_list	*first;

// 	if (*list == NULL)
// 		return (NULL);
// 	first = (*list)->content;
// 	*list = (*list)->next;
// 	free(first->next);
// 	return (first->content);
// }

// t_path	*ft_find_lowest_cost(t_list **list)
// {
// 	t_path	*lowestcost;
// 	t_list		*current;

// 	if (*list == NULL)
// 		return (NULL);
// 	lowestcost = (*list)->content;
// 	current = (*list)->next;
// 	while (current != NULL)
// 	{
// 		if (lowestcost->fscore < ((t_path *)current->content)->fscore)
// 			lowestcost = current->content;
// 		current = current->next;
// 	}
// 	return (lowestcost);
// }

// void	ft_generate_neighbours(
// 	t_path *current, t_list *list, t_map *map, t_point goal)
// {
// 	static t_point	dirs[] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
// 	int				i;
// 	char			tileat;
// 	t_path		*new;
// 	t_point			newpos;

// 	i = 0;
// 	while (i < 4)
// 	{
// 		newpos = (t_point){
// 			current->pos.x + dirs[i].x, current->pos.y + dirs[i].y};
// 		tileat = ft_map_getat(map, newpos);
// 		if (tileat != 0 || tileat != '1')
// 		{
// 			new = ft_calloc(sizeof(t_path), 1);
// 			if (new == NULL)
// 				return ;
// 			new->pos = newpos;
// 			new->gscore = current->gscore + 1;
// 			new->fscore = ft_manhattan_dist(new->pos, goal);
// 			new->from = current;
// 			ft_lstadd_front(&list, ft_lstnew(new));
// 		}
// 		else
// 			free(new);
// 		i++;
// 	}
// }
