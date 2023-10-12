/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_anim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:54:02 by nsassenb          #+#    #+#             */
/*   Updated: 2023/10/11 16:13:34 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "so_long.h"

// static char	*ft_iteratable_str(const char *org)
// {
// 	char	*new;
// 	int		len;

// 	len = ft_strlen(org);
// 	new = ft_calloc(1, len + 2);
// 	if (new == NULL)
// 		return (NULL);
// 	ft_memcpy(new, org, len);
// }

// int	ft_load_anim(t_anim *anim, const char *filepath, const char *filename)
// {
// 	char	*itername;
// 	int		len;
// 	char	*temppath;
// 	int		i;
// 	int		fd;

// 	fd = 1;
// 	i = 1;
// 	itername = ft_iteratable_str(filename);
// 	len = ft_strlen(itername);
// 	while (fd > 0)
// 	{
// 		itername[len + 1] = i + '0';
// 		temppath = ft_strjoin(filepath, itername);
// 		fd = open(temppath, O_RDONLY);
// 		ft_lstadd_back(anim->imgs, ft_lstnew(mlx_xpm_file_to_image(NULL, temppath,)))
// 		free(temppath);
// 		close(fd);
// 		i++;
// 	}
// 	free(itername);
// 	return (SUCCESS);
// }
