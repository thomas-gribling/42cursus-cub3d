/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 12:16:40 by tgriblin          #+#    #+#             */
/*   Updated: 2024/09/30 08:55:12 by tgriblin         ###   ########.fr       */
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

static int	get_texture_outside(t_game *g, char c, int x, int y)
{
	int	is_open;
	int	i;

	is_open = dist_to_tile(g, x, y) < 1.25;
	i = -1;
	while (!is_open && ++i < g->enemies_amt)
		is_open = dist_enemy(g, i, x, y) < 1.25;
	if (c == '3')
		return (TEX_DOOR_C_OUTSIDE + is_open);
	if (c == '4')
		return (TEX_WINDOW_OUTSIDE);
	return (TEX_WALL_OUTSIDE);
}

static int	get_texture_bis(t_game *g, char c, int is_open)
{
	if (c == '2')
		return (TEX_WALL_SIGN + 15 * (g->curr_level > 0));
	if (c == '3')
		return (TEX_DOOR_C + is_open + 15 * (g->curr_level > 0));
	if (c == '4')
		return (TEX_WINDOW + 12 * (g->curr_level > 0));
	if (c >= '5' && c <= '7')
		return (TEX_BOARD_1 + c - '5');
	if (c == '8' || c == '9' || c == 'A')
		return (TEX_BUSH + (c == 'A'));
	if (c == '1' && g->curr_level == 3)
		return (TEX_WALL_BACKROOMS_0);
	return (TEX_WALL + 15 * (g->curr_level > 0));
}

int	get_texture(t_game *g, int x, int y)
{
	t_cam	*ca;
	char	c;
	int		is_open;
	int		i;

	ca = g->p->cam;
	c = g->map->content[y][x];
	is_open = dist_to_tile(g, x, y) < 1.25;
	i = -1;
	while (!is_open && ++i < g->enemies_amt)
		is_open = dist_enemy(g, i, x, y) < 1.25;
	if (is_portal(g, x, y))
		return (is_portal(g, x, y));
	if (is_outside(g, ca, x, y) && c != '8' && c != '9')
		return (get_texture_outside(g, c, x, y));
	if (is_class(g, ca, x, y) && (c == '2' || c == '1'))
		return (TEX_WALL_CLASS);
	return (get_texture_bis(g, c, is_open));
}
