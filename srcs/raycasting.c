/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 08:31:44 by tgriblin          #+#    #+#             */
/*   Updated: 2024/06/11 08:39:28 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include "../include/cub3d.h"

void	raycast_draw(t_game *g, t_cam *c, int x)
{
	int	color;
	int	y;
	
	if (!c->perp_wall_dist)
		c->line_h = HEIGHT;
	else
		c->line_h = (int)(HEIGHT / c->perp_wall_dist);
	c->bounds[0] = -c->line_h / 2 + HEIGHT / 2;
	if (c->bounds[0] < 0)
		c->bounds[0] = 0;
	c->bounds[1] = c->line_h / 2 + HEIGHT / 2;
	if (c->bounds[1] >= HEIGHT)
		c->bounds[1] = HEIGHT - 1;
	color = 0xFFFFFF;
	if (c->side == 1)
		color = 0xAAAAAA;
	y = c->bounds[0];
	while (++y <= c->bounds[1])
		mlx_pixel_put(g->mlx, g->win, x, y, color);
}

void	raycast_dda(t_game *g, t_cam *c)
{
	(void)g;
	while (!c->hit)
	{
		if (c->side_dist_x < c->side_dist_y)
		{
			c->side_dist_x += c->delta_dist_x;
			c->map_x += c->step_x;
			c->side = 0;
		}
		else
		{
			c->side_dist_y += c->delta_dist_y;
			c->map_y += c->step_y;
			c->side = 1;
		}
		if (g->map->content[c->map_y][c->map_x] == '1')
			c->hit = 1;
	}
	if (c->side == 0)
		c->perp_wall_dist = (c->side_dist_x - c->delta_dist_x);
	else
		c->perp_wall_dist = (c->side_dist_y - c->delta_dist_y);
}

void	raycast_dist(t_game *g, t_cam *c)
{
	if (c->ray_dir_x < 0)
	{
		c->step_x = -1;
		c->side_dist_x = (g->p->x - c->map_x) * c->delta_dist_x;
	}
	else
	{
		c->step_x = 1;
		c->side_dist_x = (c->map_x + 1.0 - g->p->x) * c->delta_dist_x;
	}
	if (c->ray_dir_y < 0)
	{
		c->step_y = -1;
		c->side_dist_y = (g->p->y - c->map_y) * c->delta_dist_y;
	}
	else
	{
		c->step_y = 1;
		c->side_dist_y = (c->map_y + 1.0 - g->p->y) * c->delta_dist_y;
	}
}

int	raycast(t_game *g, t_cam *c)
{
	int	x;

	mlx_clear_window(g->mlx, g->win);
	x = -1;
	while (++x < WIDTH)
	{	
		c->hit = 0;
		c->map_x = (int)g->p->x;
		c->map_y = (int)g->p->y;
		c->cam_x = 2.0 * x / (double)WIDTH - 1.0;
		c->ray_dir_x = c->dir_x + c->plane_x * c->cam_x;
		c->ray_dir_y = c->dir_y + c->plane_y * c->cam_x;
		if (!c->ray_dir_x)
			c->delta_dist_x = 1e30;
		else
			c->delta_dist_x = sqrt(1 + (c->ray_dir_y * c->ray_dir_y) / (c->ray_dir_x * c->ray_dir_x));
		if (!c->ray_dir_y)
			c->delta_dist_y = 1e30;
		else
			c->delta_dist_y = sqrt(1 + (c->ray_dir_x * c->ray_dir_x) / (c->ray_dir_y * c->ray_dir_y));
		raycast_dist(g, c);
		raycast_dda(g, c);
		raycast_draw(g, c, x);
	}
	return (0);
}
