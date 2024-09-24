/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 08:54:40 by tgriblin          #+#    #+#             */
/*   Updated: 2024/09/24 11:22:13 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static void	get_vals_2(t_game *g, double *dir, double *plane, int dest_portal)
{
	if (g->portals[dest_portal].face == SOUTH)
	{
		dir[0] = 0;
		dir[1] = 1;
		plane[0] = -0.66;
		plane[1] = 0;
	}
	if (g->portals[dest_portal].face == EAST)
	{
		dir[0] = 1;
		dir[1] = 0;
		plane[0] = 0;
		plane[1] = 0.66;
	}
	if (g->portals[dest_portal].face == WEST)
	{
		dir[0] = -1;
		dir[1] = 0;
		plane[0] = 0;
		plane[1] = -0.66;
	}
}

static int	get_vals(t_game *g, t_cam *c, double *dir, double *plane)
{
	int		dest_portal;

	if (c->map_x_visible == g->portals[0].map_x
		&& c->map_y_visible == g->portals[0].map_y)
		dest_portal = 1;
	else
		dest_portal = 0;
	if (!g->portals[dest_portal].is_placed)
		return (1);
	if (g->portals[dest_portal].face == NORTH)
	{
		dir[0] = 0;
		dir[1] = -1;
		plane[0] = 0.66;
		plane[1] = 0;
	}
	/*c->map_x = g->portals[dest_portal].map_x;
	c->map_y = g->portals[dest_portal].map_y;
	if (g->portals[dest_portal].face == EAST)
		c->map_x++;
	if (g->portals[dest_portal].face == SOUTH)
		c->map_y++;*/
	get_vals_2(g, dir, plane, dest_portal);
	return (0);
}

static void	change_raycast_dist(t_game *g, t_cam *c)
{
	if (c->ray_dir_x < 0)
	{
		c->step_x = -1;
		c->side_dist_x = (g->p->x - c->map_x) * c->delta_x;
	}
	else
	{
		c->step_x = 1;
		c->side_dist_x = (c->map_x + 1.0 - g->p->x) * c->delta_x;
	}
	if (c->ray_dir_y < 0)
	{
		c->step_y = -1;
		c->side_dist_y = (g->p->y - c->map_y) * c->delta_y;
	}
	else
	{
		c->step_y = 1;
		c->side_dist_y = (c->map_y + 1.0 - g->p->y) * c->delta_y;
	}
}

void	change_raycast_dir(t_game *g, t_cam *c)
{
	double	dir[2];
	double	plane[2];

	dir[0] = 0;
	dir[1] = 0;
	plane[0] = 0;
	plane[1] = 0;
	if (get_vals(g, c, dir, plane))
		return ;
	c->ray_dir_x = dir[0] + plane[0] * c->cam_x;
	c->ray_dir_y = dir[1] + plane[1] * c->cam_x;
	if (!c->ray_dir_x)
		c->delta_x = 1e30;
	else
		c->delta_x = sqrt(1 + pow(c->ray_dir_y, 2) / pow(c->ray_dir_x, 2));
	if (!c->ray_dir_y)
		c->delta_y = 1e30;
	else
		c->delta_y = sqrt(1 + pow(c->ray_dir_x, 2) / pow(c->ray_dir_y, 2));
	change_raycast_dist(g, c);
}

int	is_it_portal(t_game *g, int x, int y)
{
	int	dir;

	dir = get_dir(g->p->cam);
	if (x == g->portals[0].map_x && y == g->portals[0].map_y
		&& dir == g->portals[0].face && g->portals[0].is_placed)
		return (1);
	if (x == g->portals[1].map_x && y == g->portals[1].map_y
		&& dir == g->portals[1].face && g->portals[1].is_placed)
		return (1);
	return (0);
}
