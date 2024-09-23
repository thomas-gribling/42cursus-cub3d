/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 12:16:40 by tgriblin          #+#    #+#             */
/*   Updated: 2024/09/23 10:38:59 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static int	is_outside(t_game *g, t_cam *c, int x, int y)
{
	if (c->side == 0 && c->ray_dir_x >= 0
		&& g->map->content[y][x - 1] == 'O')
		return (1);
	if (c->side == 0 && c->ray_dir_x < 0
		&& g->map->content[y][x + 1] == 'O')
		return (1);
	if (c->side == 1 && c->ray_dir_y >= 0
		&& g->map->content[y - 1][x] == 'O')
		return (1);
	if (c->side == 1 && c->ray_dir_y < 0
		&& g->map->content[y + 1][x] == 'O')
		return (1);
	return (0);
}

static int	is_class(t_game *g, t_cam *c, int x, int y)
{
	if (c->side == 0 && c->ray_dir_x >= 0
		&& (g->map->content[y][x - 1] == 'C'
			|| g->map->content[y][x - 1] == '4'))
		return (1);
	if (c->side == 0 && c->ray_dir_x < 0
		&& (g->map->content[y][x + 1] == 'C'
			|| g->map->content[y][x + 1] == '4'))
		return (1);
	if (c->side == 1 && c->ray_dir_y >= 0
		&& (g->map->content[y - 1][x] == 'C'
			|| g->map->content[y - 1][x] == '4'))
		return (1);
	if (c->side == 1 && c->ray_dir_y < 0
		&& (g->map->content[y + 1][x] == 'C'
			|| g->map->content[y + 1][x] == '4'))
		return (1);
	return (0);
}

double	dist_to_tile(t_game *g, int x, int y)
{
	double	dist;
	int		delta[2];

	delta[0] = fabs(x + 0.5 - g->p->x);
	delta[1] = fabs(y + 0.5 - g->p->y);
	dist = sqrt(pow(delta[0], 2) + pow(delta[1], 2));
	return (dist);
}

static int	get_texture_outside(t_game *g, char c, int x, int y)
{
	if (c == '3')
		return (TEX_DOOR_C_OUTSIDE + 1 * (dist_to_tile(g, x, y) < 1.25));
	if (c == '4')
		return (TEX_WINDOW_OUTSIDE);
	return (TEX_WALL_OUTSIDE);
}

int	get_texture(t_game *g, int x, int y)
{
	t_cam	*c;
	char	ch;

	c = g->p->cam;
	ch = g->map->content[y][x];
	if (is_outside(g, c, x, y) && ch != '8')
		return (get_texture_outside(g, ch, x, y));
	if (is_class(g, c, x, y) && (ch == '2' || ch == '1'))
		return (TEX_WALL_CLASS);
	if (ch == '2')
		return (TEX_WALL_SIGN);
	if (ch == '3')
		return (TEX_DOOR_C + 1 * (dist_to_tile(g, x, y) < 1.25));
	if (ch == '4')
		return (TEX_WINDOW);
	if (ch >= '5' && ch <= '7')
		return (TEX_BOARD_1 + ch - '5');
	if (ch == '8')
		return (TEX_BUSH);
	return (TEX_WALL);
}
