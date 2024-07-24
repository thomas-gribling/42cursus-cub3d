/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:22:53 by tgriblin          #+#    #+#             */
/*   Updated: 2024/07/24 14:38:54 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"
#include "../include/gnl.h"
#include "../mlx/mlx.h"

static void	raycast_put_pixel(t_game *g, t_cam *c, int x, int y)
{
	t_tex	tf;
	t_tex	tc; 

	tf = g->tex[TEX_FLOOR];
	tc = g->tex[TEX_CEILING];
	if (c->cell_x >= 0 && c->cell_y >= 0
		&& c->cell_x < g->map->sizes[c->cell_y] && c->cell_y < g->map->height
		&& is_prohibited_char(g->map->content[c->cell_y][c->cell_x]))
	{
	c->color = tex_get_pixel(&tf, c->tx[0], c->ty[0]);
	tex_pixel_put(&c->buff, x, y, c->color);
	c->color = tex_get_pixel(&tc, c->tx[1], c->ty[1]);
	tex_pixel_put(&c->buff, x, HEIGHT - y - 1, c->color);
	}
}

static void	raycast_cell(t_game *g, t_cam *c, int y)
{
	int		x;
	t_tex	tf;
	t_tex	tc;

	x = -1;
	tf = g->tex[TEX_FLOOR];
	tc = g->tex[TEX_CEILING];
	while (++x < WIDTH)
	{
		c->cell_x = (int)(c->floor_x);
		c->cell_y = (int)(c->floor_y);
		c->tx[0] = (int)(tf.width * (c->floor_x - c->cell_x));
		c->ty[0] = (int)(tf.height * (c->floor_y - c->cell_y));
		c->tx[1] = (int)(tc.width * (c->floor_x - c->cell_x));
		c->ty[1] = (int)(tc.height * (c->floor_y - c->cell_y));
		c->floor_x += c->floor_step_x;
		c->floor_y += c->floor_step_y;
		raycast_put_pixel(g, c, x, y);
	}
}

void	raycast_floor_ceiling(t_game *g, t_cam *c)
{
	int	y;

	y = HEIGHT / 2 - 1;
	while (++y < HEIGHT)
	{
		c->ray_dir_x_0 = c->dir_x - c->plane_x;
		c->ray_dir_y_0 = c->dir_y - c->plane_y;
		c->ray_dir_x_1 = c->dir_x + c->plane_x;
		c->ray_dir_y_1 = c->dir_y + c->plane_y;
		c->p = y - (HEIGHT - 1) / 2;
		c->pos_z = 0.5 * (HEIGHT - 1);
		c->row_distance = c->pos_z / c->p;
		c->floor_step_x = c->row_distance * (c->ray_dir_x_1 - c->ray_dir_x_0) / WIDTH;
		c->floor_step_y = c->row_distance * (c->ray_dir_y_1 - c->ray_dir_y_0) / WIDTH;
		c->floor_x = g->p->x + c->row_distance * c->ray_dir_x_0;
		c->floor_y = g->p->y + c->row_distance * c->ray_dir_y_0;
		raycast_cell(g, c, y);
	}
}
