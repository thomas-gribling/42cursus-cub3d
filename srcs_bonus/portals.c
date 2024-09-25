/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 08:54:40 by tgriblin          #+#    #+#             */
/*   Updated: 2024/09/25 11:14:08 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	is_it_portal(t_game *g, int x, int y)
{
	int	dir;

	dir = get_dir(g->p->cam);
	if (x == g->portals[0].map_x && y == g->portals[0].map_y
		&& dir == g->portals[0].face && g->portals[0].is_placed)
		return (1);
	if (x == g->portals[1].map_x && y == g->portals[1].map_y
		&& dir == g->portals[1].face && g->portals[1].is_placed)
		return (1);
	return (0);
}
