/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 08:52:48 by tgriblin          #+#    #+#             */
/*   Updated: 2024/10/04 11:07:56 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

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
		g->curr_slot = keycode - KEY_1;
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
