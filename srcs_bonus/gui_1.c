/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:44:51 by tgriblin          #+#    #+#             */
/*   Updated: 2024/10/10 11:48:52 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static void	do_draw_digits(t_game *g, t_tex *to, int *i, int *wh)
{
	int	j;

	j = i[3];
	if (i[2] == 0)
		tex_put(to, &g->tex[TEX_GUI_0 + i[0] % 10],
			wh[0] * (int_len(i[1]) - j - 1), 0);
	else if (i[2] == 1)
	{
		if (i[1] < 10)
			tex_put(to, &g->tex[TEX_GUI_0], WIDTH - wh[0] * (j + 2), 0);
		tex_put(to, &g->tex[TEX_GUI_0 + i[0] % 10],
			WIDTH - wh[0] * (j + 1), 0);
	}
	else if (i[2] == 2)
	{
		tex_put(to, &g->tex[TEX_GUI_SEP],
			WIDTH - wh[0] * (j + 2) - wh[0] / 2, 0);
		tex_put(to, &g->tex[TEX_GUI_0 + i[0] % 10],
			WIDTH - wh[0] * (j + 3) - wh[0] / 2, 0);
	}
	else if (i[2] == 3)
		tex_put(to, &g->tex[TEX_GUI_0 + i[0] % 10],
			WIDTH - wh[0] * (j + 1), wh[1]);
	i[0] /= 10;
}

void	draw_digits(t_game *g, t_tex *to, long digits, int align)
{
	int		wh[2];
	int		infos[4];
	int		i;

	wh[0] = g->tex[TEX_GUI_0].width;
	wh[1] = g->tex[TEX_GUI_0].height;
	infos[0] = digits;
	infos[1] = digits;
	infos[2] = align;
	i = -1;
	while (++i < int_len(digits))
	{
		infos[3] = i;
		do_draw_digits(g, to, infos, wh);
	}
}

static void	draw_weapons(t_game *g, t_cam *c, int curr)
{
	t_tex	t;

	if (!g->curr_slot && curr >= 300)
	{
		g->shoot_state = 0;
		g->shoot_timer = 0;
	}
	else if (!g->curr_slot && g->shoot_timer && curr >= 200)
		g->shoot_state = 1;
	else if (!g->curr_slot && g->shoot_timer && curr >= 100)
		g->shoot_state = 2;
	if (g->curr_slot && g->curr_level == 2)
		g->shoot_state = 3;
	else if (g->curr_slot && curr >= 200)
	{
		g->shoot_state = 0;
		g->shoot_timer = 0;
	}
	else if (g->curr_slot && g->shoot_timer && curr >= 100)
		g->shoot_state = 1 + 1 * (g->curr_click == RIGHT_CLICK);
	t = g->tex[TEX_GUN_0 + g->shoot_state + 3 * g->curr_slot];
	if (g->slots[0] && g->slots[1])
		tex_put_scale(&c->buff, &t, 0, 0);
}

void	draw_gui(t_game *g, t_cam *c)
{
	int		time_left;
	t_tex	t;

	t = g->tex[TEX_GUI_INV_EMPTY_0 + g->curr_slot];
	if (g->slots[0] && g->slots[1])
		t = g->tex[TEX_GUI_INV_FULL_0 + g->curr_slot];
	tex_put(&c->buff, &t, WIDTH / 2 - t.width / 2, HEIGHT - 44 - t.height);
	if (!g->hide_bullies_amt)
		draw_digits(g, &c->buff, g->bullies_amt, 0);
	time_left = ft_max(COPS_TIMER - ((get_time() - g->start) / 1000), 0);
	time_left = ft_max(time_left + g->time_m, 0);
	draw_digits(g, &c->buff, time_left % 60, 1);
	draw_digits(g, &c->buff, time_left / 60, 2);
	draw_digits(g, &c->buff, (int)floor(1.0 / g->fps), 3);
	if (g->curr_level == 2 && g->chad_phase > 0)
	{
		t = g->tex[TEX_GUI_HEALTHBAR];
		tex_put(&c->buff, &t, WIDTH / 2 - t.width / 2, 0);
		t = g->tex[TEX_GUI_HP_0 + g->p->hp - 1];
		tex_put(&c->buff, &t, 10, g->tex[TEX_GUI_0].height + 10);
		update_chad_healthbar(g);
	}
	draw_weapons(g, g->p->cam, get_time() - g->shoot_timer);
}

void	update_screen(t_game *g)
{
	t_cam	*c;

	c = g->p->cam;
	reset_buffer(&c->buff);
	raycast_floor_ceiling(g, c);
	fill_z_buffer(g);
	raycast(g, c, -1);
	raycast_z_buffer(g);
	if (c->colls)
		free(c->colls);
	c->colls = NULL;
	draw_gui(g, c);
	if (g->show_map)
		draw_minimap(g, c);
	if (get_time() - g->splash_timer <= 3000)
		tex_put(&c->buff, &g->tex[TEX_GUI_SPLASH_0 + g->curr_level],
			WIDTH / 2 - 300, HEIGHT / 2 - 225);
	mlx_put_image_to_window(g->mlx, g->win, c->buff.ptr, 0, 0);
	if (get_time() - g->last_fps_update >= 500.0)
	{
		g->fps = (get_time() - g->last_frame) / 1000.0;
		g->last_fps_update = get_time();
	}
	g->last_frame = get_time();
}
