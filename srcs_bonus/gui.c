/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:44:51 by tgriblin          #+#    #+#             */
/*   Updated: 2024/09/30 15:18:46 by tgriblin         ###   ########.fr       */
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

void	draw_gui(t_game *g, t_cam *c)
{
	int	time_left;

	if (!g->slots[0] && !g->slots[1])
		tex_put_scale(&c->buff, &g->tex[TEX_GUI_INV_00_0 + g->curr_slot], 0, 0);
	if (g->slots[0] && !g->slots[1])
		tex_put_scale(&c->buff, &g->tex[TEX_GUI_INV_10_0 + g->curr_slot], 0, 0);
	if (!g->slots[0] && g->slots[1])
		tex_put_scale(&c->buff, &g->tex[TEX_GUI_INV_01_0 + g->curr_slot], 0, 0);
	if (g->slots[0] && g->slots[1])
		tex_put_scale(&c->buff, &g->tex[TEX_GUI_INV_11_0 + g->curr_slot], 0, 0);
	if (!g->hide_bullies_amt)
		draw_digits(g, &c->buff, g->bullies_amt, 0);
	time_left = ft_max(COPS_TIMER - ((get_time() - g->start) / 1000), 0);
	draw_digits(g, &c->buff, time_left % 60, 1);
	draw_digits(g, &c->buff, time_left / 60, 2);
	draw_digits(g, &c->buff, (int)floor(1.0 / g->fps), 3);
	if (time_left == 0)
		g->scene = 2;
}

void	draw_minimap(t_game *g, t_cam *c)
{
	int		x;
	int		y;
	t_tex	tex[3];

	tex[0] = g->tex[TEX_GUI_MAPWALL];
	tex[1] = g->tex[TEX_GUI_MAPPLAYER];
	tex[2] = g->tex[TEX_GUI_0];
	y = -1;
	while (g->map->content[++y])
	{
		x = -1;
		while (g->map->content[y][++x])
		{
			if (is_collision(g->map->content[y][x])
				&& g->map->content[y][x] != ' ')
				tex_put(&c->buff, &tex[0], 10 * (x + 1),
					tex[2].height + 10 * (y + 1));
			if (g->map->content[y][x] == 'E')
				tex_put(&c->buff, &tex[1], 10 * (x + 1),
					tex[2].height + 10 * (y + 1));
		}
	}
	x = 10 * ((int)g->p->x + 1);
	y = tex[2].height + 10 * ((int)g->p->y + 1);
	tex_put(&c->buff, &g->tex[TEX_GUI_MAPPLAYER], x, y);
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
