/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:12:53 by nsassenb          #+#    #+#             */
/*   Updated: 2023/10/09 18:20:11 by nsassenb         ###   ########.fr       */
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
# define SPACE_KEY 0x0020
# define L_CONTROL_KEY 0xffe3

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_map
{
	char	**lines;
	t_point	size;
	int		pcount;
	int		ccount;
	int		ecount;
}	t_map;

typedef enum e_error
{
	SUCCESS = 0,
	MALLOC_FAIL,
	NO_FILE ,
	NOT_RECTANGLE,
	INVALID_SIGNS,
	INACCESIBLE,
	INVALID_MAP,
	PLAYER_NUM

}	t_error;

//read_map.c
int		ft_read_map(t_map *map, const char *file);
//read_map_utils.c
void	ft_free_map(t_map *map);
//check_map.c
int		ft_check_validsigns(t_map *map);
t_point	ft_get_playerpos(t_map *map);
int		ft_check_map(t_map *map);

#endif //!SO_LONG_H