/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:36:56 by tgriblin          #+#    #+#             */
/*   Updated: 2024/10/10 11:41:48 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	tp_player_spawn(t_game *g)
{
	fill_z_buffer(g);
	if (g->curr_level == 0)
	{
		turn_player_to(g->p->cam, SOUTH);
		g->p->x = 14.5;
		g->p->y = 5.5;
	}
	if (g->curr_level == 1)
	{
		turn_player_to(g->p->cam, WEST);
		g->p->x = 27.5;
		g->p->y = 2.5;
	}
	if (g->curr_level == 2)
	{
		turn_player_to(g->p->cam, EAST);
		g->p->x = 1.5;
		g->p->y = 3.5;
	}
	if (g->curr_level == 3)
	{
		turn_player_to(g->p->cam, EAST);
		g->p->x = 46.5;
		g->p->y = 37.5;
	}
}

static void	change_level(t_game *g, int dest)
{
	g->curr_level = dest;
	g->portals[0].is_placed = 0;
	g->portals[1].is_placed = 0;
	g->map = g->maps[g->curr_level];
	if (g->curr_level != 2)
		g->splash_timer = get_time();
	free_enemies(g);
	if (g->curr_level == 1)
		generate_enemies(g, 3);
	if (g->curr_level == 2)
		generate_enemies(g, -1);
	if (g->curr_level == 3)
	{
		g->slots[0] = 0;
		g->slots[1] = 0;
		g->show_map = 0;
		g->hide_bullies_amt = 1;
		generate_enemies(g, -2);
	}
	tp_player_spawn(g);
	stopallsounds(g);
	if (g->curr_level == 1)
		playsoundloop(g, MUS_LVL2, MUS_LVL2_DUR);
	else if (g->curr_level == 3)
		playsoundloop(g, MUS_BACKROOMS, MUS_BACKROOMS_DUR);
}

void	apply_moves(t_game *g, double *new)
{
	if (g->freeze_player)
		return ;
	if (!is_collision(g->map->content[(int)g->p->y][(int)new[0]]))
		g->p->x = new[0];
	if (!is_collision(g->map->content[(int)new[1]][(int)g->p->x]))
		g->p->y = new[1];
	if (g->map->content[(int)g->p->y][(int)g->p->x] == 'E' && g->bullies_amt)
		change_level(g, 1);
	if (g->map->content[(int)g->p->y][(int)g->p->x] == 'S')
		change_level(g, 3);
	do_portals(g);
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

void	rotate_player(t_game *g, t_cam *c, int keycode)
{
	double	tmp;

	if (g->freeze_player)
		return ;
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
