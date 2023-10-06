/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:12:53 by nsassenb          #+#    #+#             */
/*   Updated: 2023/10/06 13:08:20 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include "get_next_line_bonus.h"
# include "libft.h"

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_map
{
	char	**map;
	t_point	size;
}	t_map;


t_map	read_map(const char *file);




#endif //!SO_LONG_H