/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:47:39 by tgriblin          #+#    #+#             */
/*   Updated: 2024/10/10 11:50:39 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	draw_credits(t_game *g)
{
	t_tex	t;

	if (g->ending)
		return ;
	t = g->tex[TEX_CREDITS_0 + g->credits_curr];
	tex_put(&g->p->cam->buff, &t, WIDTH / 2 - t.width / 2, g->credits_y);
	if (!(g->credits_curr == 2 && g->credits_y == HEIGHT / 2 - t.height / 2))
		g->credits_y -= 2;
	if (g->credits_y < 0 - t.height && g->credits_curr < 2)
	{
		g->credits_curr++;
		g->credits_y = HEIGHT;
	}
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
