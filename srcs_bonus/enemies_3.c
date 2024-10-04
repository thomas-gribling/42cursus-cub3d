/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 07:57:03 by tgriblin          #+#    #+#             */
/*   Updated: 2024/10/04 08:56:10 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

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
	if (e->type == BULLY)
		g->bullies_amt--;
	if (e->type == STUDENT)
		g->time_m -= 20;
}

void	update_chad_healthbar(t_game *g)
{
	int	bounds[2];
	int	thickness;
	int	x;
	int	y;

	bounds[0] = WIDTH / 2 - 200;
	bounds[1] = bounds[0] + g->chad_hp * 4;
	y = 99;
	thickness = 10 + y + 1;
	while (++y < thickness && g->chad_hp)
	{
		x = bounds[0] - 1;
		while (++x < bounds[1])
			tex_pixel_put(&g->p->cam->buff, x, y, 0x00CC00);
	}
}

void	update_chad(t_game *g)
{
	char	*entrance;
	char	*exit;

	entrance = &g->map->content[3][16];
	exit = &g->map->content[3][22];
	if (g->p->x >= 17.5 && !g->chad_timer)
	{
		g->chad_timer = get_time();
		g->freeze_player = 1;
		*entrance = '1';
		g->splash_timer = get_time();
	}
	if (g->chad_timer && get_time() - g->chad_timer > 3000 && !g->chad_phase)
	{
		g->chad_phase = 1;
		g->freeze_player = 0;
	}
	//if (g->chad_phase > 0 && !g->enemies[0].is_dead)
	//{
	//	
	//}
	if (g->enemies[0].is_dead && *exit == '1')
		*exit = '3';
	if (g->p->x > 33.5)
		g->scene = 2;
}
