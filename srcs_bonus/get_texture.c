/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 12:16:40 by tgriblin          #+#    #+#             */
/*   Updated: 2024/09/17 10:31:25 by tgriblin         ###   ########.fr       */
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

static int	get_texture_outside(char c)
{
	if (c == '3')
		return (TEX_DOOR_C_OUTSIDE);
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
	if (is_outside(g, c, x, y) && ch != '9' && ch != 'A')
		return (get_texture_outside(ch));
	if (ch == '2')
		return (TEX_WALL_SIGN);
	if (ch == '3')
		return (TEX_DOOR_C);
	if (ch == '4')
		return (TEX_WINDOW);
	if (ch == '5')
		return (TEX_WALL_CLASS);
	if (ch >= '6' && ch <= '8')
		return (TEX_BOARD_1 + ch - '0' - 6);
	if (ch == '9')
		return (TEX_WALL_BRICKS);
	if (ch == 'A')
		return (TEX_BUSH);
	return (TEX_WALL);
}
