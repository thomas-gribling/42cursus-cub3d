/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 09:01:16 by tgriblin          #+#    #+#             */
/*   Updated: 2024/10/02 09:03:47 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static void	tp_portal(t_game *g, int dest)
{
	if (g->portals[dest].face == NORTH)
	{
		g->p->x = g->portals[dest].map_x + 0.5;
		g->p->y = g->portals[dest].map_y - 0.2;
	}
	if (g->portals[dest].face == SOUTH)
	{
		g->p->x = g->portals[dest].map_x + 0.5;
		g->p->y = g->portals[dest].map_y + 1.2;
	}
	if (g->portals[dest].face == WEST)
	{
		g->p->x = g->portals[dest].map_x - 0.2;
		g->p->y = g->portals[dest].map_y + 0.5;
	}
	if (g->portals[dest].face == EAST)
	{
		g->p->x = g->portals[dest].map_x + 1.2;
		g->p->y = g->portals[dest].map_y + 0.5;
	}
	turn_player_to(g->p->cam, g->portals[dest].face);
}

void	do_portals(t_game *g)
{
	int	i;

	if (!g->portals[0].is_placed || !g->portals[1].is_placed)
		return ;
	i = -1;
	while (++i < 2)
	{
		if (g->portals[i].face == NORTH && (int)g->p->x == g->portals[i].map_x
			&& fabs(g->p->y - g->portals[i].map_y) < 0.1)
			tp_portal(g, 1 - i);
		if (g->portals[i].face == SOUTH && (int)g->p->x == g->portals[i].map_x
			&& fabs(g->p->y - (g->portals[i].map_y + 1)) < 0.1)
			tp_portal(g, 1 - i);
		if (g->portals[i].face == WEST
			&& fabs(g->p->x - g->portals[i].map_x) < 0.1
			&& (int)g->p->y == g->portals[i].map_y)
			tp_portal(g, 1 - i);
		if (g->portals[i].face == EAST
			&& fabs(g->p->x - (g->portals[i].map_x + 1)) < 0.1
			&& (int)g->p->y == g->portals[i].map_y)
			tp_portal(g, 1 - i);
	}
}
