/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 08:31:44 by tgriblin          #+#    #+#             */
/*   Updated: 2024/06/11 10:44:24 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include "../include/cub3d.h"

static void	raycast_draw(t_game *g, t_cam *c, int x)
{
	//int	color;
	int		y;
	t_tex	tex;
	(void)x;
	
	tex = g->tex[TEX_WALL];
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
	c->step = 1.0 * tex.height / c->line_h;
	c->tex_pos = (c->bounds[0] - HEIGHT / 2 + c->line_h / 2) * c->step;
	y = c->bounds[0];
	while (++y < c->bounds[1])
	{
		c->tex_y = (int)c->tex_pos & (tex.height - 1);
		c->tex_pos += c->step;
		c->color = 0xFFFFFF;
		if (c->side == 1)
			c->color = (c->color >> 1) & 0x7F7F7F;
		
	}
	/*color = 0xFFFFFF;
	if (c->side == 1)
		color = 0xAAAAAA;
	y = c->bounds[0];
	while (++y <= c->bounds[1])
		mlx_pixel_put(g->mlx, g->win, x, y, color);*/
}

static void raycast_tex(t_game *g, t_cam *c)
{
	if (c->side == 0)
		c->wall_x = g->p->y + c->perp_wall_dist * c->ray_dir_y;
	else
		c->wall_x = g->p->x + c->perp_wall_dist * c->ray_dir_x;
	c->wall_x -= floor(c->wall_x);
	c->tex_x = (int)(c->wall_x * (double)g->tex[TEX_WALL].width);
	if ((!c->side && c->ray_dir_x > 0) || (c->side == 1 && c->ray_dir_y < 0))
		c->tex_x = g->tex[TEX_WALL].width - c->tex_x - 1;
}

static void	raycast_dda(t_game *g, t_cam *c)
{
	double	tmp;
	
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
		tmp = (c->map_x - g->p->x + (1 - c->step_x) / 2) / c->ray_dir_x;
	else
		tmp = (c->map_y - g->p->y + (1 - c->step_y) / 2) / c->ray_dir_y;
	c->perp_wall_dist = tmp;
}

static void	raycast_dist(t_game *g, t_cam *c)
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
		raycast_tex(g, c);
		raycast_draw(g, c, x);
	}
	return (0);
}
