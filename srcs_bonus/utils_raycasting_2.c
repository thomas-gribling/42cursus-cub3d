/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_raycasting_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 20:05:47 by tgriblin          #+#    #+#             */
/*   Updated: 2024/10/07 10:07:16 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	get_texture_spr(t_game *g, t_sprite spr)
{
	char	c;
	int		x;
	int		y;

	x = (int)floor(spr.x);
	y = (int)floor(spr.y);
	c = g->map->content[y][x];
	if (c == 'T')
		return (TEX_SPR_TREE_0 + (x + y) % 2);
	if (c == 'Z')
		return (TEX_LOVEGIMP);
	return (TEX_SPR_TREE_0);
}

void	raycast_step(t_cam *c)
{
	if (c->side_dist_x < c->side_dist_y)
	{
		c->side_dist_x += c->delta_x;
		c->map_x += c->step_x;
		c->side = 0;
	}
	else
	{
		c->side_dist_y += c->delta_y;
		c->map_y += c->step_y;
		c->side = 1;
	}
}

int	get_dir(t_cam *c)
{
	int	dir;

	if (c->side == 0 && c->ray_dir_x >= 0)
		dir = WEST;
	if (c->side == 0 && c->ray_dir_x < 0)
		dir = EAST;
	if (c->side == 1 && c->ray_dir_y >= 0)
		dir = NORTH;
	if (c->side == 1 && c->ray_dir_y < 0)
		dir = SOUTH;
	return (dir);
}

void	save_looking_at(t_game *g, t_coll *co)
{
	g->looking_x = co->map_x;
	g->looking_y = co->map_y;
	g->side = co->side;
	g->ray_dir_x = co->ray_dir_x;
	g->ray_dir_y = co->ray_dir_y;
}

void	save_to_coll(t_game *g, t_cam *c, t_coll *tmp)
{
	tmp->map_x = c->map_x;
	tmp->map_y = c->map_y;
	tmp->side = c->side;
	tmp->tex = g->tex[get_texture(g, c->map_x, c->map_y)];
	tmp->solid = 1;
	tmp->ray_dir_x = c->ray_dir_x;
	tmp->ray_dir_y = c->ray_dir_y;
	tmp->step_x = c->step_x;
	tmp->step_y = c->step_y;
}
