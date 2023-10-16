/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:59:29 by nsassenb          #+#    #+#             */
/*   Updated: 2023/10/14 18:49:29 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	ft_vector_double(t_vector *vect)
{
	t_path	*new;
	int		cpyi;

	new = ft_calloc(sizeof(t_path), vect->capacity * 2);
	if (new == NULL)
		return (1);
	cpyi = 0;
	while (cpyi < vect->size)
	{
		new[cpyi] = vect->data[cpyi];
		cpyi++;
	}
	free(vect->data);
	vect->data = new;
	vect->capacity *= 2;
	return (0);
}

int	ft_vector_add(t_vector *vect, t_path item)
{
	if (vect->capacity == 0 || vect->data == NULL)
	{
		vect->data = ft_calloc(sizeof(t_path), 2);
		if (vect->data == NULL)
			return (1);
		vect->capacity = 2;
	}
	else if (vect->size >= vect->capacity)
	{
		if (ft_vector_double(vect))
			return (1);
	}
	vect->data[vect->size++] = item;
	return (0);
}

void	ft_vector_clear(t_vector *vec)
{
	free(vec->data);
	vec->size = 0;
	vec->capacity = 0;
	vec->data = NULL;
}

int	ft_vector_remove(t_vector *vect, int indx)
{
	if (indx >= vect->size)
		return (1);
	if (indx + 1 >= vect->capacity)
		return (1);
	ft_memmove(&vect->data[indx],
		&vect->data[indx + 1],
		sizeof(t_path) * ((vect->size - 1) - indx));
	vect->size--;
	ft_bzero(&vect->data[vect->size], sizeof(t_path));
	return (0);
}

t_path	ft_vector_pop(t_vector *vect)
{
	t_path	first;

	first.distance = -1;
	if (vect->size < 1)
		return (first);
	first = vect->data[0];
	ft_vector_remove(vect, 0);
	return (first);
}
