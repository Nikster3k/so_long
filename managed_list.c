/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   managed_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 17:24:11 by nsassenb          #+#    #+#             */
/*   Updated: 2023/10/08 18:16:36 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_clear_ml_data(t_ml *list)
{
	int	i;

	i = 0;
	while (i < list->size)
		free(list->data[i++]);
}

int	ft_ml_pushback(t_ml *list, char *str)
{
	char	**newlist;
	int		cpyi;

	if (list->capacity == 0 || list->data == NULL)
	{
		list->data = malloc(sizeof(char *) * 2);
		if (list->data == NULL)
			return (0);
		list->capacity = 2;
	}
	else if (list->size >= list->capacity)
	{
		newlist = ft_calloc(sizeof(char *), list->capacity * 2);
		if (newlist == NULL)
			return (0);
		cpyi = 0;
		while (cpyi < list->size)
		{
			newlist[cpyi] = list->data[cpyi];
			cpyi++;
		}
		free(list->data);
		list->data = newlist;
		list->capacity = list->capacity * 2;
	}
	list->data[list->size] = str;
	list->size++;
	return (1);
}

void	ft_fullfree_ml(t_ml *ml)
{
	ft_clear_ml_data(ml);
	free(ml->data);
}
