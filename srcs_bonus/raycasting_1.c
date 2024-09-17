/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 08:31:44 by tgriblin          #+#    #+#             */
/*   Updated: 2024/09/17 10:47:48 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include "../include/cub3d_bonus.h"

static void	raycast_fill_buffer(t_cam *c, int x, int curr)
{
	int		y;
	t_coll	co;

	co = c->colls[curr];
	c->bounds[0] = -c->line_h / 2 + HEIGHT / 2;
	if (c->bounds[0] < 0)
		c->bounds[0] = 0;
	c->bounds[1] = c->line_h / 2 + HEIGHT / 2;
	if (c->bounds[1] > HEIGHT)
		c->bounds[1] = HEIGHT;
	c->step = 1.0 * co.tex.height / c->line_h;
	c->tex_pos = (c->bounds[0] - HEIGHT / 2 + c->line_h / 2) * c->step;
	y = c->bounds[0] - 1;
	/*if (co.tex_id == TEX_WALL_OUTSIDE || co.tex_id == TEX_WINDOW_OUTSIDE
		|| co.tex_id == TEX_DOOR_C_OUTSIDE)
		y = c->bounds[0] - c->line_h * 2 - 1;*/
	while (++y < c->bounds[1])
	{
		c->tex_y = (int)c->tex_pos & (co.tex.endian - 1);
		//if (c->tex_y < co.tex.height * 3)
		//	c->tex_y %= co.tex.height;
		c->tex_pos += c->step;
		c->color = tex_get_pixel(&co.tex, co.tex.width - c->tex_x - 1, c->tex_y);
		tex_pixel_put(&c->buff, x, y, c->color);
	}
}

static void	raycast_tex(t_game *g, t_cam *c, int x, int curr)
{
	t_coll	co;
	double	tmp;

	co = c->colls[curr];
	if (co.side == 0)
		tmp = (co.map_x - g->p->x + (1 - c->step_x) / 2) / c->ray_dir_x;
	else
		tmp = (co.map_y - g->p->y + (1 - c->step_y) / 2) / c->ray_dir_y;
	c->perp_wall_dist = tmp;
	if (co.side == 0)
		c->wall_x = g->p->y + c->perp_wall_dist * c->ray_dir_y;
	else
		c->wall_x = g->p->x + c->perp_wall_dist * c->ray_dir_x;
	c->wall_x -= floor(c->wall_x);
	c->tex_x = (int)(c->wall_x * (double)co.tex.width);
	if ((!co.side && c->ray_dir_x > 0) || (co.side == 1 && c->ray_dir_y < 0))
		c->tex_x = co.tex.width - c->tex_x - 1;
	if (!c->perp_wall_dist)
		c->line_h = HEIGHT;
	else
		c->line_h = (int)(HEIGHT / c->perp_wall_dist);
	raycast_fill_buffer(c, x, curr);
}

static void	raycast_dda(t_game *g, t_cam *c, int x)
{
	int	i;

	while (!c->hit)
	{
		raycast_step(c);
		if (is_bounds(g, c->map_x, c->map_y))
			c->hit = 1;
		if (is_castable(g->map->content[c->map_y][c->map_x]))
		{
			c->colls = append_colls(c->colls, c, g);
			if (!is_transparent(g->map->content[c->map_y][c->map_x]))
				c->hit = 1;
			while (c->map_x == c->colls[c->colls_amt].map_x
				&& c->map_y == c->colls[c->colls_amt].map_y)
				raycast_step(c);
		}
	}
	i = c->colls_amt;
	while (--i >= 0)
		raycast_tex(g, c, x, i);
}

static void	raycast_dist(t_game *g, t_cam *c, int x)
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
	raycast_dda(g, c, x);
}

void	raycast(t_game *g, t_cam *c, int x)
{
	while (++x < WIDTH)
	{
		c->hit = 0;
		c->map_x = (int)g->p->x;
		c->map_y = (int)g->p->y;
		c->cam_x = 2.0 * x / (double)WIDTH - 1.0;
		c->ray_dir_x = c->dir_x + c->plane_x * c->cam_x;
		c->ray_dir_y = c->dir_y + c->plane_y * c->cam_x;
		c->colls_amt = 0;
		if (!c->ray_dir_x)
			c->delta_x = 1e30;
		else
			c->delta_x = sqrt(1 + pow(c->ray_dir_y, 2) / pow(c->ray_dir_x, 2));
		if (!c->ray_dir_y)
			c->delta_y = 1e30;
		else
			c->delta_y = sqrt(1 + pow(c->ray_dir_x, 2) / pow(c->ray_dir_y, 2));
		raycast_dist(g, c, x);
	}
}
