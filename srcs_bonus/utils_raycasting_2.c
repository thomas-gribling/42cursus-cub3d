/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_raycasting_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 20:05:47 by tgriblin          #+#    #+#             */
/*   Updated: 2024/09/23 09:35:58 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

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
		{
			new[i].map_x = old[i].map_x;
			new[i].map_y = old[i].map_y;
			new[i].side = old[i].side;
			new[i].tex = old[i].tex;
			new[i].tex_id = old[i].tex_id;
		}
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
	/*if (spr.x >= g->p->x && spr.y >= g->p->y)
		return (TEX_SPR_TREE_0);
	if (spr.x < g->p->x && spr.y >= g->p->y)
		return (TEX_SPR_TREE_0);
	if (spr.x >= g->p->x && spr.y < g->p->y)
		return (TEX_SPR_TREE_1);
	if (spr.x < g->p->x && spr.y < g->p->y)
		return (TEX_SPR_TREE_1);*/
	if (c == 'T')
		return (TEX_SPR_TREE_0 + (x + y) % 2);
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
