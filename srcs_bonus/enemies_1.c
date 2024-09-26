/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:10:26 by tgriblin          #+#    #+#             */
/*   Updated: 2024/09/26 10:05:10 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static void	check_moves(t_game *g, t_enemy *e)
{
	double	p[2];

	p[0] = e->x;
	p[1] = e->y;
	if (e->type == STUDENT || e->type == BULLY)
	{
		p[0] = e->x + 0.05 * e->dirx;
		p[1] = e->y + 0.05 * e->diry;
	}
	if (e->type >= NEXTBOT_1 && e->type <= NEXTBOT_3)
	{
		p[0] = e->x - 0.05 * (-1 + 2 * ((g->p->x < e->x)));
		p[1] = e->y - 0.05 * (-1 + 2 * ((g->p->y < e->y)));
	}
	if (p[0] < 0)
		p[0] = 0;
	if (p[1] < 0)
		p[1] = 0;
	if (!is_collision(g->map->content[(int)e->y][(int)p[0]]))
		e->x = p[0];
	if (!is_collision(g->map->content[(int)p[1]][(int)e->x]))
		e->y = p[1];
}

void	update_enemies(t_game *g)
{
	int		i;

	i = -1;
	while (++i < g->enemies_amt)
	{
		if (!g->enemies[i].is_dead)
		{
			if (rand() % 10 == 0)
				g->enemies[i].dirx = -1 + 2 * (rand() % 2);
			if (rand() % 10 == 0)
				g->enemies[i].diry = -1 + 2 * (rand() % 2);
			check_moves(g, &g->enemies[i]);
		}
	}
}

void	free_enemies(t_game *g)
{
	if (g->enemies)
	{
		free(g->enemies);
		g->enemies = NULL;
		g->enemies_amt = 0;
	}
}
