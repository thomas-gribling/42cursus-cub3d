/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:44:51 by tgriblin          #+#    #+#             */
/*   Updated: 2024/09/25 18:23:49 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	draw_digits(t_game *g, t_tex *to, long digits, int align)
{
	int		digit_w;
	int		digit_h;
	long	tmp;
	int		i;

	digit_w = g->tex[TEX_GUI_0].width;
	digit_h = g->tex[TEX_GUI_0].height;
	tmp = digits;
	i = -1;
	while (++i < int_len(digits))
	{
		if (align == 0)
			tex_put(to, &g->tex[TEX_GUI_0 + tmp % 10], digit_w * (int_len(digits) - i - 1), 0);
		else if (align == 1)
		{
			if (digits < 10)
				tex_put(to, &g->tex[TEX_GUI_0], WIDTH - digit_w * (i + 2), 0);
			tex_put(to, &g->tex[TEX_GUI_0 + tmp % 10], WIDTH - digit_w * (i + 1), 0);
		}
		else if (align == 2)
		{
			tex_put(to, &g->tex[TEX_GUI_SEP], WIDTH - digit_w * (i + 2) - digit_w / 2, 0);
			tex_put(to, &g->tex[TEX_GUI_0 + tmp % 10], WIDTH - digit_w * (i + 3) - digit_w / 2, 0);
		}
		else if (align == 3)
			tex_put(to, &g->tex[TEX_GUI_0 + tmp % 10], WIDTH - digit_w * (i + 1), digit_h);
		tmp /= 10;
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
	t_tex	tex[2];

	tex[0] = g->tex[TEX_GUI_MAPWALL];
	tex[1] = g->tex[TEX_GUI_0];
	y = -1;
	while (g->map->content[++y])
	{
		x = -1;
		while (g->map->content[y][++x])
			if (is_collision(g->map->content[y][x]) && g->map->content[y][x] != ' ')
				tex_put(&c->buff, &tex[0], 10 * (x + 1), tex[1].height + 10 * (y + 1));
	}
	x = 10 * ((int)g->p->x + 1);
	y = tex[1].height + 10 * ((int)g->p->y + 1);
	tex_put(&c->buff, &g->tex[TEX_GUI_MAPPLAYER], x, y);
}

void	update_screen(t_game *g)
{
	t_cam	*c;

	c = g->p->cam;
	reset_buffer(&c->buff);
	raycast_floor_ceiling(g, c);
	raycast(g, c, -1);
	raycast_z_buffer(g);
	if (c->colls)
		free(c->colls);
	c->colls = NULL;
	draw_gui(g, c);
	if (g->show_map)
		draw_minimap(g, c);
	if (get_time() - g->splash_timer <= 3000)
		tex_put_scale(&c->buff, &g->tex[TEX_GUI_SPLASH_0 + g->curr_level], 0, 0);
	mlx_put_image_to_window(g->mlx, g->win, c->buff.ptr, 0, 0);
	if (get_time() - g->last_fps_update >= 500.0)
	{
		g->fps = (get_time() - g->last_frame) / 1000.0;
		g->last_fps_update = get_time();
	}
	g->last_frame = get_time();
}
