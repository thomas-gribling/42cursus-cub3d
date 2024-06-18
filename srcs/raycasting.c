/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 08:31:44 by tgriblin          #+#    #+#             */
/*   Updated: 2024/06/18 16:59:57 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include "../include/cub3d.h"

static int	get_wall_tex(t_cam *c)
{
	int	tex;

	if (c->side == 0 && c->ray_dir_x >= 0)
		tex = TEX_WALL_N;
	if (c->side == 0 && c->ray_dir_x < 0)
		tex = TEX_WALL_S;
	if (c->side == 1 && c->ray_dir_y >= 0)
		tex = TEX_WALL_W;
	if (c->side == 1 && c->ray_dir_y < 0)
		tex = TEX_WALL_E;
	return (tex);
}

static void	raycast_fill_buffer(t_game *g, t_cam *c, int x)
{
	int		y;
	t_tex	tex;

	tex = g->tex[get_wall_tex(c)];
	c->step = 1.0 * tex.height / c->line_h;
	c->tex_pos = (c->bounds[0] - HEIGHT / 2 + c->line_h / 2) * c->step;
	y = c->bounds[0];
	while (++y < c->bounds[1])
	{
		c->tex_y = (int)c->tex_pos & (tex.endian - 1);
		c->tex_pos += c->step;
		c->color = tex_get_pixel(&tex, c->tex_x, c->tex_y);
		tex_pixel_put(&c->buff, x, y, c->color);
	}
}

static void	raycast_get_pixels(t_game *g, t_cam *c, int x)
{
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
	raycast_fill_buffer(g, c, x);
}

static void	raycast_tex(t_game *g, t_cam *c, int x)
{
	t_tex	tex;

	tex = g->tex[get_wall_tex(c)];
	if (c->side == 0)
		c->wall_x = g->p->y + c->perp_wall_dist * c->ray_dir_y;
	else
		c->wall_x = g->p->x + c->perp_wall_dist * c->ray_dir_x;
	c->wall_x -= floor(c->wall_x);
	c->tex_x = (int)(c->wall_x * (double)tex.width);
	if ((!c->side && c->ray_dir_x > 0) || (c->side == 1 && c->ray_dir_y < 0))
		c->tex_x = tex.width - c->tex_x - 1;
	raycast_get_pixels(g, c, x);
}

static void	raycast_dda(t_game *g, t_cam *c, int x)
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
	raycast_tex(g, c, x);
}

static void	raycast_dist(t_game *g, t_cam *c, int x)
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
	raycast_dda(g, c, x);
}

int	raycast(t_game *g, t_cam *c)
{
	int	x;

	mlx_clear_window(g->mlx, g->win);
	reset_buffer(g, &c->buff);
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
		raycast_dist(g, c, x);
	}
	mlx_put_image_to_window(g->mlx, g->win, c->buff.ptr, 0, 0);
	return (0);
}
