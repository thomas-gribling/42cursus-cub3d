/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_raycasting_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 20:05:47 by tgriblin          #+#    #+#             */
/*   Updated: 2024/09/18 20:05:58 by tgriblin         ###   ########.fr       */
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

int	get_texture_spr(char c)
{
	if (c == 'T')
		return (TEX_SPR_TREE_0 + rand() % 2);
	return (TEX_SPR_TREE_0);
}

void	append_spr(t_game *g, t_map *map, int x, int y)
{
	t_sprite	*new;
	int			i;

	i = 0;
	new = malloc((map->spr_amt + 1) * sizeof(t_sprite));
	if (map->spr)
	{
		i = -1;
		while (++i < map->spr_amt)
		{
			new[i].x = map->spr[i].x;
			new[i].y = map->spr[i].y;
			new[i].dist = map->spr[i].dist;
			new[i].tex_id = map->spr[i].tex_id;
		}
	}
	new[i].x = x + 0.5;
	new[i].y = y + 0.5;
	new[i].dist = 0.0;
	new[i].tex_id = get_texture_spr(g->map->content[y][x]);
	map->spr_amt++;
	free(map->spr);
	map->spr = new;
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
