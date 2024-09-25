/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_raycasting_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 20:05:47 by tgriblin          #+#    #+#             */
/*   Updated: 2024/09/25 17:39:40 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static void	copy_old(t_coll *new, t_coll *old)
{
	new->map_x = old->map_x;
	new->map_y = old->map_y;
	new->side = old->side;
	new->tex = old->tex;
	new->tex_id = old->tex_id;
}

t_coll	*append_colls(t_coll *old, t_cam *c, t_game *g)
{
	t_coll	*new;
	int		i;

	i = 0;
	new = malloc((c->colls_amt + 1) * sizeof(t_coll));
	if (old)
	{
		i = -1;
		while (++i < c->colls_amt)
			copy_old(&new[i], &old[i]);
	}
	new[i].map_x = c->map_x;
	new[i].map_y = c->map_y;
	new[i].side = c->side;
	new[i].tex = g->tex[get_texture(g, c->map_x, c->map_y)];
	new[i].tex_id = get_texture(g, c->map_x, c->map_y);
	c->colls_amt++;
	free(old);
	return (new);
}

int	get_texture_spr(t_game *g, t_sprite spr)
{
	char	c;
	int		x;
	int		y;

	x = (int)floor(spr.x);
	y = (int)floor(spr.y);
	c = g->map->content[y][x];
	if (c == 'B')
		return (TEX_NPC_CHAD_H);
	if (c == 'T')
		return (TEX_SPR_TREE_0 + (x + y) % 2);
	if (c == 'E')
		return (TEX_SPR_LADDER);
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

double	dist_to_tile(t_game *g, double x, double y)
{
	double	dist;
	double	delta[2];

	delta[0] = x + 0.5 - g->p->x;
	delta[1] = y + 0.5 - g->p->y;
	dist = sqrt(pow(delta[0], 2) + pow(delta[1], 2));
	return (dist);
}

double	dist_enemy(t_game *g, int i, double x, double y)
{
	double	dist;
	double	delta[2];

	delta[0] = x + 0.5 - g->enemies[i].x;
	delta[1] = y + 0.5 - g->enemies[i].y;
	dist = sqrt(pow(delta[0], 2) + pow(delta[1], 2));
	return (dist);
}
