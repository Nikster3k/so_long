/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 18:41:51 by nsassenb          #+#    #+#             */
/*   Updated: 2023/10/12 18:57:17 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	abs(int x)
{
	if (x < 0)
		return (-x);
	return (x);
}

void	*ft_lstfind(t_list **lst, void *data, size_t size)
{
	t_list	*current;

	current = *lst;
	while (current != NULL)
	{
		if (ft_memcmp(current->content, data, size))
			return (current->content);
		current = current->next;
	}
	return (NULL);
}

int	compare_point_fscore(t_list *fscore, t_point a, t_point b)
{
	
}

int	ft_manhattan_dist(t_point lhs, t_point rhs)
{
	return (abs((lhs.x - rhs.x) + (lhs.y - rhs.x)));
}
