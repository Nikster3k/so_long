/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:12:53 by nsassenb          #+#    #+#             */
/*   Updated: 2023/10/15 19:46:39 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <fcntl.h>
# include <mlx.h>
# include "get_next_line_bonus.h"
# include "printf/ft_printf.h"

# define IMG_SIZE 32

# define KEY_ESCAPE 0xff1b
# define KEY_SPACE 0x0020
# define KEY_L_CONTROL 0xffe3
# define KEY_W 0x0077
# define KEY_A 0x0061
# define KEY_S 0x0073
# define KEY_D 0x0064

typedef enum e_error
{
	SUCCESS,
	MALLOC_FAIL,
	NO_FILE ,
	NOT_RECTANGLE,
	INVALID_SIGNS,
	INACCESSIBLE,
	INVALID_MAP,
	LEAK_MAP,
	PLAYER_NUM
}	t_error;

typedef enum e_tile_type
{
	FLOOR = '0',
	WALL = '1',
	COLLECTABLE = 'C',
	PLAYER = 'P',
	EXIT = 'E',
	PATROL = 'G'
}	t_etype;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_pathnode
{
	t_point	pos;
	int		distance;
}	t_path;

typedef struct s_vector
{
	t_path	*data;
	int		size;
	int		capacity;
}	t_vector;

typedef struct s_map
{
	char	**lines;
	t_point	size;
	t_point	pstart;
	t_point	exitpos;
	int		pcount;
	int		ccount;
	int		ecount;
	int		gcount;
}	t_map;

typedef struct s_image
{
	void	*img_ptr;
}	t_image;

typedef struct s_anim_img
{
	t_image	*imgs;
	int		animlen;
	int		current;
}	t_anim;

typedef struct s_entity
{
	t_point	pos;
	t_anim	sprite;
}	t_entity;

typedef struct s_enemy
{
	t_entity	base;
	t_point		movdir;
}	t_enemy;

typedef struct s_player
{
	t_entity	ent;
	int			collected;
	int			moves;
}	t_player;

typedef struct s_animator
{
	t_list	*anims;
}	t_animator;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_map		map;
	t_player	player;
	t_enemy		*enems;
	t_anim		enem_anim;
	t_animator	animator;
	t_image		wall;
	t_image		ground;
	t_image		coin;
	t_image		exit;
	int			minmoves;
	int			savemoves;
}	t_game;

//read_map_utils.c
int		ft_read_map(t_map *map, const char *file);
//read_map.c
void	ft_free_map_strings(t_map *map);
void	ft_free_map(t_map *map);
int		ft_create_map(t_map *map, const char *filepath);
//check_map.c
t_point	ft_get_playerpos(t_map *map);
int		ft_check_map(t_map *map);
char	ft_map_getat(t_map *map, t_point pos);
//check_map_extra.c
int		ft_check_for_leaks(t_map *filled);
int		ft_clone_map(t_map	*map, t_map *copy);
//map_utils.c
t_point	ft_getposof(t_map *map, char c);
//player_movment.c
int		ft_move_entity(t_entity *ent, t_point dir);
int		ft_check_player_move(t_game *game, t_point dir);
//draw_fts.c
void	ft_swap_img(void *mlx_ptr, t_image *img, char *path);
void	ft_draw_map(t_game *game);
void	ft_draw_player(t_game *game);
void	ft_draw_at(t_game *game, t_point pos);
void	ft_draw_all(t_game *game);
//load_images.c
void	*ft_load_image(void *mlx_ptr, char *filepath);
int		ft_initialize_images(t_game *game);
//load_anim.c
int		ft_load_anim(t_game *game, t_anim *anim, const char *filepath,
			char **filenames);
int		ft_destroy_animation(void *mlx_ptr, t_anim *anim);
//print_error.c
int		ft_print_error(int errnum);
//utils.c
int		ft_safestrlen(const char *s);
//dynamic_list.c
int		ft_vector_add(t_vector *vect, t_path item);
void	ft_vector_clear(t_vector *vec);
int		ft_vector_remove(t_vector *vect, int indx);
t_path	ft_vector_pop(t_vector *vect);
//shortest_path.c
int		ft_shortest_moves(t_map *map, t_point start, t_point goal);
//game_utils.c
int		ft_keyhook(int keycode, t_game *game);
void	ft_initialize_func_hooks(t_game *game);
int		ft_destroy_game(t_game *game, int err);
void	ft_initialize_game(t_game *game);
//enemy.c
int		ft_initialize_enemies(t_game *game);
void	ft_move_enemies(t_game *game);
//animator.c
int		ft_update_animations(t_animator *animator);

#endif //!SO_LONG_H