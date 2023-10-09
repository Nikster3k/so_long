/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:12:53 by nsassenb          #+#    #+#             */
/*   Updated: 2023/10/09 12:24:56 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <mlx.h>
# include <X11/keysymdef.h>
# include "get_next_line_bonus.h"
# include "printf/ft_printf.h"

# define ESCAPE_KEY 0xff1b

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_managed_string_list
{
	char	**data;
	size_t	size;
	size_t	capacity;
}	t_ml;

void	ft_clear_ml_data(t_ml *ml);
int		ft_ml_pushback(t_ml *list, char *str);
void	ft_fullfree_ml(t_ml *ml);

typedef struct s_map
{
	t_ml	mlist;
	t_point	size;
}	t_map;

int		ft_read_map(t_map *map, const char *file);

#endif //!SO_LONG_H