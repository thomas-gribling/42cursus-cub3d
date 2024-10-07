/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:10:26 by tgriblin          #+#    #+#             */
/*   Updated: 2024/10/07 09:33:02 by tgriblin         ###   ########.fr       */
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

static void	check_moves(t_game *g, t_enemy *e, double speed)
{
	double	p[2];

	p[0] = e->x;
	p[1] = e->y;
	if (e->type == STUDENT || e->type == BULLY)
	{
		p[0] = e->x + speed * e->dirx;
		p[1] = e->y + speed * e->diry;
	}
	if ((e->type >= NEXTBOT_1 && e->type <= NEXTBOT_3)
		|| e->type == BULLY_BALL)
	{
		p[0] = e->x - speed * (-1 + 2 * ((g->p->x < e->x)));
		p[1] = e->y - speed * (-1 + 2 * ((g->p->y < e->y)));
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

static void	calc_dirs(t_game *g, int i)
{
	if (rand() % 10 == 0)
	{
		g->enemies[i].dirx = rand() % 3 - 1;
		if (g->enemies[i].dirx == g->enemies[i].olddirx)
			g->enemies[i].back = 0;
		else
			g->enemies[i].back = 1;
	}
	if (rand() % 10 == 0)
	{
		g->enemies[i].diry = rand() % 3 - 1;
		if (g->enemies[i].dirx == g->enemies[i].olddirx)
			g->enemies[i].back = 0;
		else if (g->enemies[i].back)
			g->enemies[i].back = 1;
	}
	g->enemies[i].olddirx = g->enemies[i].dirx;
	g->enemies[i].olddiry = g->enemies[i].diry;
}

static void	check_kill(t_game *g, t_enemy *e)
{
	int	kill;

	kill = 0;
	if (e->type >= NEXTBOT_1
		&& e->type <= NEXTBOT_3
		&& dist_to_tile(g, e->x, e->y) < 0.85)
		kill = 5;
	if (e->type == BULLY_BALL && fabs(e->x - g->p->x) < 0.4
		&& fabs(e->y - g->p->y) < 0.4)
	{
		g->p->hp--;
		g->bullies_amt--;
		e->is_dead = 1;
	}
	if (!g->p->hp)
		kill = 3;
	if (kill)
	{
		g->ending = kill;
		g->scene = 2;
	}
}

void	update_enemies(t_game *g)
{
	int		i;

	i = -1;
	while (++i < g->enemies_amt)
	{
		if (!g->enemies[i].is_dead)
		{
			calc_dirs(g, i);
			if (g->enemies[i].type == BULLY_BALL)
				check_moves(g, &g->enemies[i], 0.01);
			else
				check_moves(g, &g->enemies[i], 0.05);
			check_kill(g, &g->enemies[i]);
		}
	}
}
