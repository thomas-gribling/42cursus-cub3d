/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 09:37:57 by tgriblin          #+#    #+#             */
/*   Updated: 2024/10/02 08:59:44 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static void	place_portal(t_game *g, int i)
{
	int	face;

	if (g->side == 0 && g->ray_dir_x >= 0)
		face = WEST;
	if (g->side == 0 && g->ray_dir_x < 0)
		face = EAST;
	if (g->side == 1 && g->ray_dir_y >= 0)
		face = NORTH;
	if (g->side == 1 && g->ray_dir_y < 0)
		face = SOUTH;
	if (g->portals[1 - i].is_placed && g->portals[1 - i].map_x == g->looking_x
		&& g->portals[1 - i].map_y == g->looking_y
		&& g->portals[1 - i].face == face)
		return ;
	g->portals[i].map_x = g->looking_x;
	g->portals[i].map_y = g->looking_y;
	g->portals[i].face = face;
	g->portals[i].is_placed = 1;
}

static void	use_weapon(t_game *g, int button)
{
	if (button == LEFT_CLICK && g->curr_slot == 1 && g->slots[1] == 1)
		place_portal(g, 0);
	if (button == RIGHT_CLICK && g->curr_slot == 1 && g->slots[1] == 1)
		place_portal(g, 1);
	if (button == LEFT_CLICK && g->curr_slot == 0 && g->slots[0] == 1
		&& get_time() - g->start > 100.0)
		shoot_enemy(g);
}

static int	mouse_click(int button, int x, int y, t_game *g)
{
	(void)x;
	(void)y;
	if (g->scene == 0 && button == LEFT_CLICK)
	{
		g->scene = 1;
		g->start = get_time();
		g->last_frame = g->start;
		g->splash_timer = g->start;
		//mlx_mouse_hide(g->mlx, g->win);
		mlx_destroy_image(g->mlx, g->tmp_tex.ptr);
	}
	if (g->scene == 1)
	{
		if ((button == WHEEL_DOWN || button == WHEEL_UP)
			&& get_time() - g->last_wheel > 300.0)
		{
			g->last_wheel = get_time();
			g->curr_slot = !g->curr_slot;
		}
		if (button == LEFT_CLICK || button == RIGHT_CLICK)
			use_weapon(g, button);
	}
	return (0);
}

int	mouse_move(int x, int y, t_game *g)
{
	int	move;

	(void)y;
	if (g->scene != 1)
		return (0);
	move = 0;
	if (x > g->mouse_middle_x || x > WIDTH - 11)
		move = KEY_RIGHT;
	else if (x < g->mouse_middle_x || x < 10)
		move = KEY_LEFT;
	if (move)
	{
		rotate_player(g->p->cam, move);
		g->mouse_middle_x = x;
	}
	return (0);
}

void	do_hooks(t_game *g)
{
	mlx_hook(g->win, 2, 1L << 0, key_pressed, g);
	mlx_hook(g->win, 3, 1L << 1, key_released, g);
	mlx_hook(g->win, 17, 0L, close_game, g);
	mlx_hook(g->win, 4, 1L << 2, mouse_click, g);
	mlx_hook(g->win, 6, 1L << 6, mouse_move, g);
	mlx_loop_hook(g->mlx, main_loop, g);
}
