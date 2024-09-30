/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:10:26 by tgriblin          #+#    #+#             */
/*   Updated: 2024/09/30 18:20:32 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static int	check_moves_nextbots(t_game *g, t_enemy *e, double *p)
{
	if (e->type < NEXTBOT_1 || e->type > NEXTBOT_3)
		return (0);
	if (!is_collision(g->map->content[(int)e->y][(int)p[0]])
		&& fabs(e->x - g->p->x) > 0.1)
		e->x = p[0];
	if (!is_collision(g->map->content[(int)p[1]][(int)e->x])
		&& fabs(e->y - g->p->y) > 0.1)
		e->y = p[1];
	return (1);
}

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
	if (check_moves_nextbots(g, e, p))
		return ;
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
				g->enemies[i].dirx = rand() % 3 - 1;
			if (rand() % 10 == 0)
				g->enemies[i].diry = rand() % 3 - 1;
			check_moves(g, &g->enemies[i]);
			if (g->enemies[i].type >= NEXTBOT_1
				&& g->enemies[i].type <= NEXTBOT_1
				&& dist_to_tile(g, g->enemies[i].x, g->enemies[i].y) < 0.75)
			{
				g->ending = 5;
				g->scene = 2;
			}
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
