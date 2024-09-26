/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_raycasting_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 08:32:04 by tgriblin          #+#    #+#             */
/*   Updated: 2024/09/26 08:38:46 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	is_collision(char c)
{
	if (c == '3' || c == '9')
		return (0);
	return (is_castable(c));
}

int	is_castable(char c)
{
	if (c >= '1' && c <= '9')
		return (1);
	if (c == 'A')
		return (1);
	return (0);
}

int	is_transparent(char c)
{
	if (c == '3' || c == '4')
		return (1);
	return (0);
}

int	is_sprite(char c)
{
	if (c == 'T' || c == 'E' || c == 'B')
		return (1);
	return (0);
}

int	is_bounds(t_game *g, int x, int y)
{
	t_map	*map;

	map = g->map;
	if (x <= 0 || y <= 0 || y >= map->height || x >= map->sizes[y])
		return (1);
	return (0);
}
