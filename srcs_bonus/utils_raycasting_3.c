/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_raycasting_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:56:35 by tgriblin          #+#    #+#             */
/*   Updated: 2024/09/25 19:51:48 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

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

t_coll	*dup_coll(t_coll *old, t_cam *c)
{
	t_coll	*new;

	new = malloc(sizeof(t_coll));
	new->x = old->x;
	new->tex = old->tex;
	new->map_x = c->map_x;
	new->map_y = c->map_y;
	new->side = c->side;
	new->ray_dir_x = c->ray_dir_x;
	new->ray_dir_y = c->ray_dir_y;
	new->step_x = c->step_x;
	new->step_y = c->step_y;
	new->solid = 0;
	new->dist = 0.0;
	return (new);
}
