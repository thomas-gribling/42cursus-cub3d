/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 07:57:03 by tgriblin          #+#    #+#             */
/*   Updated: 2024/10/10 11:51:01 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static void	clean_bodies(t_game *g)
{
	t_enemy	*new;

	new = malloc(sizeof(t_enemy));
	new[0] = copy_enemy(&g->enemies[0]);
	free_enemies(g);
	g->enemies_amt = 1;
	g->enemies = new;
}

static void	chad_generate(t_game *g)
{
	t_enemy	*new;

	new = malloc(6 * sizeof(t_enemy));
	new[0] = copy_enemy(&g->enemies[0]);
	free_enemies(g);
	g->enemies_amt = 6;
	g->enemies = new;
	generate_one_enemy(g, 1, 1);
	generate_one_enemy(g, 1, 2);
	generate_one_enemy(g, 1, 3);
	generate_one_enemy(g, 1, 4);
	generate_one_enemy(g, 1, 5);
	new[1].x = 19.5;
	new[1].y = 2.5;
	new[2].x = 19.5;
	new[2].y = 3.5;
	new[3].x = 19.5;
	new[3].y = 4.5;
	new[4].x = 17.5;
	new[4].y = 1.5;
	new[5].x = 17.5;
	new[5].y = 5.5;
	if (!g->bullies_amt)
		chad_generate(g);
}

static void	update_chad_fight(t_game *g)
{
	if (g->chad_phase == 1)
	{
		if (!g->chad_timer)
			g->chad_timer = get_time();
		if (g->chad_timer
			&& (int)(get_time() - g->chad_timer) >= (3000 + rand() % 2001))
		{
			g->chad_phase = 2;
			g->chad_timer = 1;
		}
	}
	if (g->chad_phase == 2)
	{
		if (g->chad_timer == 1)
		{
			chad_generate(g);
			g->chad_timer = 0;
		}
		if (g->bullies_amt == 0)
		{
			clean_bodies(g);
			g->chad_phase = 1;
		}
	}
}

static void	update_chad_bis(t_game *g, char *exit)
{
	if (g->chad_timer && get_time() - g->chad_timer >= 3000 && !g->chad_phase)
	{
		g->chad_phase = 1;
		g->freeze_player = 0;
		g->chad_timer = 0;
		playsoundloop(g, MUS_BOSS, MUS_BOSS_DUR);
	}
	if (!g->enemies[0].is_dead)
		update_chad_fight(g);
	if (g->enemies[0].is_dead && *exit == '1')
	{
		*exit = '3';
		stopallsounds(g);
	}
	if (g->p->x > 33.5)
	{
		g->scene = 2;
		playsound(MUS_END, 0, 0, 0);
	}
}

void	update_chad(t_game *g)
{
	char	*entrance;
	char	*exit;

	entrance = &g->map->content[3][16];
	exit = &g->map->content[3][22];
	if (g->p->x >= 17.5 && !g->chad_timer && !g->chad_phase)
	{
		g->chad_timer = get_time();
		g->freeze_player = 1;
		*entrance = '1';
		g->splash_timer = get_time();
	}
	update_chad_bis(g, exit);
}
