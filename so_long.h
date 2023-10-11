/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:12:53 by nsassenb          #+#    #+#             */
/*   Updated: 2023/10/11 14:34:43 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <mlx.h>
# include <X11/keysymdef.h>
# include "get_next_line_bonus.h"
# include "printf/ft_printf.h"

# define KEY_ESCAPE 0xff1b
# define KEY_SPACE 0x0020
# define KEY_L_CONTROL 0xffe3
# define KEY_W 0x0077
# define KEY_A 0x0061
# define KEY_S 0x0073
# define KEY_D 0x0064

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_map
{
	char	**lines;
	t_point	size;
	t_point	pstart;
	int		pcount;
	int		ccount;
	int		ecount;
}	t_map;

typedef struct s_image
{
	void	*img_ptr;
	t_point	size;
}	t_image;

typedef enum e_entity_type
{
	FLOOR,
	WALL,
	COLLECTABLE,
	PLAYER,
	EXIT,
	PATROL
}	t_etype;

typedef struct s_entity
{
	t_point		pos;
	t_image		sprite;
	t_etype		type;
}	t_entity;

typedef enum e_error
{
	MALLOC_FAIL = -7,
	NO_FILE ,
	NOT_RECTANGLE,
	INVALID_SIGNS,
	INACCESIBLE,
	INVALID_MAP,
	PLAYER_NUM,
	SUCCESS
}	t_error;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_map		map;
	t_entity	player;
	t_image		wall;
	t_image		ground;
}	t_game;

//read_map_utils.c
int		ft_read_map(t_map *map, const char *file);
//read_map.c
void	ft_free_map_strings(t_map *map);
void	ft_free_map(t_map *map);
int		ft_create_map(t_map *map, const char *filepath);
//check_map.c
int		ft_check_validsigns(t_map *map);
t_point	ft_get_playerpos(t_map *map);
int		ft_check_map(t_map *map);
char	ft_map_getat(t_map *map, t_point pos);
//check_map_extra.c
int		ft_check_for_leaks(t_map *filled);
//player_movment.c
int		ft_move_player(t_entity *player, t_map *map, t_point dir);
int		ft_coll(t_entity *player, t_map *map, t_point dir);

#endif //!SO_LONG_H