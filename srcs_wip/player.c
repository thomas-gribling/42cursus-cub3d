/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:36:56 by tgriblin          #+#    #+#             */
/*   Updated: 2024/09/16 08:35:22 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	switch_slots(t_game *g, int keycode)
{
	if (keycode == KEY_1)
		g->curr_slot = 0;
	else
		g->curr_slot = 1;
}

void	apply_moves(t_game *g, double *new)
{
	if (!is_collision(g->map->content[(int)g->p->y][(int)new[0]]))
		g->p->x = new[0];
	if (!is_collision(g->map->content[(int)new[1]][(int)g->p->x]))
		g->p->y = new[1];
}

void	move_player(t_game *g, t_cam *c, int keycode)
{
	double	new[2];

	new[0] = 0;
	new[1] = 0;
	if (keycode == KEY_W)
	{
		new[0] = g->p->x + c->dir_x * c->speed_m;
		new[1] = g->p->y + c->dir_y * c->speed_m;
	}
	if (keycode == KEY_S)
	{
		new[0] = g->p->x - c->dir_x * c->speed_m;
		new[1] = g->p->y - c->dir_y * c->speed_m;
	}
	if (keycode == KEY_A)
	{
		new[0] = g->p->x + c->dir_y * c->speed_m;
		new[1] = g->p->y - c->dir_x * c->speed_m;
	}
	if (keycode == KEY_D)
	{
		new[0] = g->p->x - c->dir_y * c->speed_m;
		new[1] = g->p->y + c->dir_x * c->speed_m;
	}
	apply_moves(g, new);
}

void	rotate_player(t_cam *c, int keycode)
{
	double	tmp;

	if (keycode == KEY_RIGHT)
	{
		tmp = c->dir_x;
		c->dir_x = tmp * cos(c->speed_r) - c->dir_y * sin(c->speed_r);
		c->dir_y = tmp * sin(c->speed_r) + c->dir_y * cos(c->speed_r);
		tmp = c->plane_x;
		c->plane_x = tmp * cos(c->speed_r) - c->plane_y * sin(c->speed_r);
		c->plane_y = tmp * sin(c->speed_r) + c->plane_y * cos(c->speed_r);
	}
	if (keycode == KEY_LEFT)
	{
		tmp = c->dir_x;
		c->dir_x = tmp * cos(-c->speed_r) - c->dir_y * sin(-c->speed_r);
		c->dir_y = tmp * sin(-c->speed_r) + c->dir_y * cos(-c->speed_r);
		tmp = c->plane_x;
		c->plane_x = tmp * cos(-c->speed_r) - c->plane_y * sin(-c->speed_r);
		c->plane_y = tmp * sin(-c->speed_r) + c->plane_y * cos(-c->speed_r);
	}
}
