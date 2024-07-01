/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:49:10 by tgriblin          #+#    #+#             */
/*   Updated: 2024/07/01 11:59:12 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"
#include "../include/gnl.h"

int	check_map_format(char *map)
{
	int	i;

	if (!map)
		return (1);
	i = 0;
	while (map[i])
		i++;
	if (i < 4)
		return (1);
	i--;
	if (map[i] == 'b')
		if (map[i - 1] == 'u')
			if (map[i - 2] == 'c')
				if (map[i - 3] == '.')
					return (0);
	return (1);
}
