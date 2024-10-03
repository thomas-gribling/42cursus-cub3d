/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 08:43:24 by tgriblin          #+#    #+#             */
/*   Updated: 2024/10/03 13:57:12 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static void	draw_minimap_tile(t_game *g, t_cam *c, int x, int y)
{
	t_tex	tex[3];

	tex[0] = g->tex[TEX_GUI_MAPWALL];
	tex[1] = g->tex[TEX_GUI_MAPEXIT];
	tex[2] = g->tex[TEX_GUI_0];
	if (is_collision(g->map->content[y][x])
		&& g->map->content[y][x] != ' ')
		tex_put(&c->buff, &tex[0], 10 * (x + 1),
			tex[2].height + 10 * (y + 1));
	if (g->map->content[y][x] == 'E')
		tex_put(&c->buff, &tex[1], 10 * (x + 1),
			tex[2].height + 10 * (y + 1));
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
	tex_put(&c->buff, &g->tex[TEX_GUI_MAPPLAYER], x, y);
}
