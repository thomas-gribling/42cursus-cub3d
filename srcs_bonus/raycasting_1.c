/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 08:31:44 by tgriblin          #+#    #+#             */
/*   Updated: 2024/09/30 08:53:26 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static void	raycast_fill_buffer(t_cam *c, int x, t_coll co)
{
	int		y;
	t_tex	tex;

	tex = co.tex;
	c->bounds[0] = -c->line_h / 2 + HEIGHT / 2;
	if (c->bounds[0] < 0)
		c->bounds[0] = 0;
	c->bounds[1] = c->line_h / 2 + HEIGHT / 2;
	if (c->bounds[1] > HEIGHT)
		c->bounds[1] = HEIGHT;
	c->step = 1.0 * tex.height / c->line_h;
	c->tex_pos = (c->bounds[0] - HEIGHT / 2 + c->line_h / 2) * c->step;
	y = c->bounds[0] - 1;
	while (++y < c->bounds[1])
	{
		c->tex_y = (int)c->tex_pos & (tex.endian - 1);
		c->tex_pos += c->step;
		c->color = tex_get_pixel(&tex, tex.width - c->tex_x - 1, c->tex_y);
		tex_pixel_put(&c->buff, x, y, c->color);
	}
	if (co.solid == 1)
		c->z_buffer[x] = c->perp_wall_dist;
}

void	raycast_tex(t_game *g, t_cam *c, int x, t_coll co)
{
	double	tmp;

	if (co.side == 0)
		tmp = (co.map_x - g->p->x + (1 - co.step_x) / 2) / co.ray_dir_x;
	else
		tmp = (co.map_y - g->p->y + (1 - co.step_y) / 2) / co.ray_dir_y;
	c->perp_wall_dist = tmp;
	if (co.side == 0)
		c->wall_x = g->p->y + c->perp_wall_dist * co.ray_dir_y;
	else
		c->wall_x = g->p->x + c->perp_wall_dist * co.ray_dir_x;
	c->wall_x -= floor(c->wall_x);
	c->tex_x = (int)(c->wall_x * (double)co.tex.width);
	if ((!co.side && co.ray_dir_x > 0) || (co.side == 1 && co.ray_dir_y < 0))
		c->tex_x = co.tex.width - c->tex_x - 1;
	if (!c->perp_wall_dist)
		c->line_h = HEIGHT;
	else
		c->line_h = (int)(HEIGHT / c->perp_wall_dist);
	raycast_fill_buffer(c, x, co);
}

static void	raycast_dda(t_game *g, t_cam *c, int x)
{
	t_coll	tmp;

	while (!c->hit)
	{
		raycast_step(c);
		tmp.x = x;
		if (is_bounds(g, c->map_x, c->map_y))
			c->hit = 1;
		if (is_castable(g->map->content[c->map_y][c->map_x]))
		{
			tmp.tex = g->tex[get_texture(g, c->map_x, c->map_y)];
			if (!is_transparent(g, g->map->content[c->map_y][c->map_x]))
				c->hit = 1;
			else
				append_z_buffer(g, (void *)dup_coll(&tmp, c), WALL);
		}
	}
	tmp.map_x = c->map_x;
	tmp.map_y = c->map_y;
	tmp.side = c->side;
	tmp.tex = g->tex[get_texture(g, c->map_x, c->map_y)];
	tmp.solid = 1;
	tmp.ray_dir_x = c->ray_dir_x;
	tmp.ray_dir_y = c->ray_dir_y;
	tmp.step_x = c->step_x;
	tmp.step_y = c->step_y;
	raycast_tex(g, c, x, tmp);
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
