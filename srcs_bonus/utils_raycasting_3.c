/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_raycasting_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:06:30 by tgriblin          #+#    #+#             */
/*   Updated: 2024/09/25 11:04:55 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

t_coll	*copy_coll(t_coll *old)
{
	t_coll	*new;

	if (!old)
		return (NULL);
	new = malloc(sizeof(t_coll));
	new->map_x = old->map_x;
	new->map_y = old->map_y;
	new->side = old->side;
	new->tex_id = old->tex_id;
	return (new);
}

static void	copy_old_actor(t_actor *old, t_actor *new)
{
	new->type = old->type;
	if (new->type == WALL)
		new->t1 = old->t1;
	if (new->type == SPRITE)
		new->t2 = old->t2;
	if (new->type == ENEMY)
		new->t3 = old->t3;
}

void	append_actor(t_game *g, t_coll *t1, t_sprite *t2, t_enemy *t3)
{
	int	i;
	t_actor	*new;

	i = 0;
	new = malloc((g->z_buffer_size + 1) * sizeof(t_actor));
	if (g->z_buffer)
	{
		i = -1;
		while (++i < g->z_buffer_size)
			copy_old_actor(new, g->z_buffer);
	}
	new[i].t1 = NULL;
	new[i].t2 = NULL;
	new[i].t3 = NULL;
	if (!t2 && !t3)
	{
		new[i].type = WALL;
		new[i].dist = dist_to_tile(g, t1->map_x, t1->map_y);
		new[i].t1 = t1;
	}
	if (!t1 && !t3)
	{
		new[i].type = SPRITE;
		new[i].dist = dist_to_tile(g, t2->x, t2->x);
		new[i].t2 = t2;
	}
	if (!t1 && !t2)
	{
		new[i].type = ENEMY;
		new[i].dist = dist_to_tile(g, t3->x, t3->y);
		new[i].t3 = t3;
	}
	g->z_buffer_size++;
}
