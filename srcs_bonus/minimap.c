/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 08:43:24 by tgriblin          #+#    #+#             */
/*   Updated: 2024/10/07 12:27:26 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static void	draw_minimap_tile(t_game *g, t_cam *c, int x, int y)
{
	t_tex	tex[4];
	int		xpos;
	int		ypos;

	tex[0] = g->tex[TEX_GUI_MAPWALL];
	tex[1] = g->tex[TEX_GUI_MAPEXIT];
	tex[2] = g->tex[TEX_GUI_0];
	tex[3] = g->tex[TEX_GUI_HP_0];
	xpos = 10 * (x + 1);
	ypos = tex[2].height + 10 * (y + 1);
	if (g->curr_level == 2 && g->chad_phase > 0)
		ypos += tex[3].height;
	if (is_collision(g->map->content[y][x])
		&& g->map->content[y][x] != ' ')
		tex_put(&c->buff, &tex[0], xpos, ypos);
	if (g->map->content[y][x] == 'E')
		tex_put(&c->buff, &tex[1], xpos, ypos);
}

void	draw_minimap(t_game *g, t_cam *c)
{
	int		x;
	int		y;

	y = -1;
	while (g->map->content[++y])
	{
		x = -1;
		while (g->map->content[y][++x])
			draw_minimap_tile(g, g->p->cam, x, y);
	}
	x = 10 * ((int)g->p->x + 1);
	y = g->tex[TEX_GUI_0].height + 10 * ((int)g->p->y + 1);
	if (g->curr_level == 2 && g->chad_phase > 0)
		y += g->tex[TEX_GUI_HP_0].height;
	tex_put(&c->buff, &g->tex[TEX_GUI_MAPPLAYER], x, y);
}
