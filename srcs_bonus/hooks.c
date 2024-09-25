/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 09:37:57 by tgriblin          #+#    #+#             */
/*   Updated: 2024/09/25 09:42:43 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"
#include "../mlx/mlx.h"

int	key_pressed(int keycode, t_game *g)
{
	if (keycode == KEY_ESCAPE)
		close_game(g);
	if (g->scene != 1)
		return (0);
	if ((keycode == KEY_W || keycode == KEY_S) && !g->p->moving_x)
		g->p->moving_x = keycode;
	if ((keycode == KEY_A || keycode == KEY_D) && !g->p->moving_y)
		g->p->moving_y = keycode;
	if ((keycode == KEY_RIGHT || keycode == KEY_LEFT) && !g->p->rotating)
		g->p->rotating = keycode;
	if (keycode == KEY_1 || keycode == KEY_2)
		switch_slots(g, keycode);
	if (keycode == KEY_TAB && g->curr_level != 3)
		g->show_map = !g->show_map;
	return (0);
}

int	key_released(int keycode, t_game *g)
{
	if (g->scene != 1)
		return (0);
	if ((keycode == KEY_W || keycode == KEY_S) && g->p->moving_x)
		g->p->moving_x = 0;
	if ((keycode == KEY_A || keycode == KEY_D) && g->p->moving_y)
		g->p->moving_y = 0;
	if ((keycode == KEY_RIGHT || keycode == KEY_LEFT) && g->p->rotating)
		g->p->rotating = 0;
	return (0);
}

int	mouse_click(int button, int x, int y, t_game *g)
{
	(void)x;
	(void)y;
	if (g->scene == 0 && button == LEFT_CLICK)
	{
		g->scene = 1;
		g->start = get_time();
		g->last_frame = g->start;
		g->splash_timer = g->start;
		mlx_mouse_hide(g->mlx, g->win);
		mlx_destroy_image(g->mlx, g->tmp_tex.ptr);
	}
	if (g->scene == 1 && (button == WHEEL_DOWN || button == WHEEL_UP))
	{
		if (get_time() - g->last_wheel > 300.0)
		{
			g->last_wheel = get_time();
			g->curr_slot = !g->curr_slot;
		}
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
