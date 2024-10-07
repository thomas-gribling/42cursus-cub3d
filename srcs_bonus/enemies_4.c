/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 09:31:00 by tgriblin          #+#    #+#             */
/*   Updated: 2024/10/07 09:32:43 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	free_enemies(t_game *g)
{
	if (g->enemies)
	{
		free(g->enemies);
		g->enemies = NULL;
		g->enemies_amt = 0;
	}
}

t_enemy	copy_enemy(t_enemy *old)
{
	t_enemy	new;

	new.back = old->back;
	new.dirx = old->dirx;
	new.diry = old->diry;
	new.dist = old->dist;
	new.id = old->id;
	new.is_dead = old->is_dead;
	new.olddirx = old->olddirx;
	new.olddiry = old->olddiry;
	new.type = old->type;
	new.x = old->x;
	new.y = old->y;
	return (new);
}

void	shoot_enemy(t_game *g)
{
	t_enemy	*e;

	if (g->id_shootable == -1 || g->enemies[g->id_shootable].is_dead)
		return ;
	e = &g->enemies[g->id_shootable];
	if (e->type == CHAD && !e->is_dead && g->chad_phase == 1)
		g->chad_hp--;
	if (e->type != CHAD || g->chad_hp == 0)
		e->is_dead = 1;
	if ((e->type == BULLY && g->curr_level != 2)
		|| e->type == BULLY_BALL)
		g->bullies_amt--;
	if (e->type == BULLY && g->curr_level == 2)
	{
		e->type = BULLY_BALL;
		e->is_dead = 0;
	}
	if (e->type == STUDENT)
		g->time_m -= 20;
}
