/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:44:51 by tgriblin          #+#    #+#             */
/*   Updated: 2024/09/12 09:41:35 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"
#include "../mlx/mlx.h"

void	draw_digits(t_game *g, t_tex *to, long digits, int align)
{
	int		digit_w;
	long	tmp;
	int		i;

	digit_w = g->tex[TEX_GUI_0].width;
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
	draw_digits(g, &c->buff, 42, 0);
	time_left = ft_max(COPS_TIMER - ((get_time() - g->start) / 1000), 0);
	draw_digits(g, &c->buff, time_left % 60, 1);
	draw_digits(g, &c->buff, time_left / 60, 2);
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
			if (!is_prohibited_char(g->map->content[y][x]) && g->map->content[y][x] != ' ')
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
	//mlx_do_sync(g->mlx);
	reset_buffer(&c->buff);
	raycast_floor_ceiling(g, c);
	raycast(g, c, -1);
	draw_gui(g, c);
	if (g->show_map)
		draw_minimap(g, c);
	mlx_clear_window(g->mlx, g->win);
	mlx_put_image_to_window(g->mlx, g->win, c->buff.ptr, 0, 0);
}
