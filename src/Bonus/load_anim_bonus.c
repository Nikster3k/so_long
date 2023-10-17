/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_anim_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:54:02 by nsassenb          #+#    #+#             */
/*   Updated: 2023/10/17 15:58:52 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static int	ft_count_filenames(char **filenames)
{
	int	count;

	count = 0;
	while (filenames[count] != NULL)
		count++;
	return (count);
}

int	ft_destroy_animation(void *mlx_ptr, t_anim *anim)
{
	int	i;

	i = 0;
	while (i < anim->animlen)
	{
		if (anim->imgs[i].img_ptr != NULL)
			mlx_destroy_image(mlx_ptr, anim->imgs[i].img_ptr);
		i++;
	}
	free(anim->imgs);
	anim->imgs = NULL;
	return (SUCCESS);
}

int	ft_load_anim(
	t_game *game, t_anim *anim, const char *filepath, char **filenames)
{
	char	*temppath;
	int		count;
	int		i;

	count = ft_count_filenames(filenames);
	anim->animlen = count;
	anim->imgs = ft_calloc(sizeof(t_image), count);
	if (anim->imgs == NULL)
		return (MALLOC_FAIL);
	i = 0;
	while (i < count)
	{
		temppath = ft_strjoin(filepath, filenames[i]);
		anim->imgs[i].img_ptr = ft_load_image(game->mlx_ptr, temppath);
		if (anim->imgs[i].img_ptr == NULL)
		{
			ft_destroy_animation(game->mlx_ptr, anim);
			free(temppath);
			return (MALLOC_FAIL);
		}
		free(temppath);
		i++;
	}
	ft_lstadd_front(&game->animator.anims, ft_lstnew(anim));
	return (SUCCESS);
}
