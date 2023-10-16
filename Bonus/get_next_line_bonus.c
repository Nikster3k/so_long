/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:18:14 by nsassenb          #+#    #+#             */
/*   Updated: 2023/10/16 12:05:32 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_cstmstrlen(char *s)
{
	int	count;

	count = 0;
	if (s == NULL)
		return (count);
	while (s[count])
		count++;
	return (count);
}

char	*get_next_line(int fd)
{
	static void		*buffers[1024];
	char			*str;
	size_t			size;

	if (fd < 0)
		return (NULL);
	size = BUFFER_SIZE + 1;
	if (buffers[fd] == NULL)
	{
		buffers[fd] = malloc(size);
		if (buffers[fd] == NULL)
			return (NULL);
		while (size--)
			((char *)buffers[fd])[size] = 0;
	}
	str = read_file(fd, &buffers[fd]);
	return (str);
}
