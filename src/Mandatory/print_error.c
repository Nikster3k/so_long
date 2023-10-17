/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:19:09 by nsassenb          #+#    #+#             */
/*   Updated: 2023/10/17 16:34:57 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_print_error(int errnum)
{
	if (errnum == SUCCESS)
		return (SUCCESS);
	ft_printf("Error\n");
	if (errnum == MALLOC_FAIL)
		ft_printf("Malloc failure.\n");
	else if (errnum == NO_FILE)
		ft_printf("File not found.\n");
	else if (errnum == NOT_RECTANGLE)
		ft_printf("Map is not Rectangular.\n");
	else if (errnum == INVALID_SIGNS)
		ft_printf("Invalid signs in map.\n");
	else if (errnum == INACCESSIBLE)
		ft_printf("Inaccessible coins or exit.\n");
	else if (errnum == INVALID_MAP)
		ft_printf("Map is invalid\n");
	else if (errnum == LEAK_MAP)
		ft_printf("Map is not enclosed.\n");
	else if (errnum == PLAYER_NUM)
		ft_printf("No player or exit.\n");
	return (errnum);
}
