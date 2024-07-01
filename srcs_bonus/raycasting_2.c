/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:22:53 by tgriblin          #+#    #+#             */
/*   Updated: 2024/07/01 16:07:37 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"
#include "../mlx/mlx.h"

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
		c->tx = (int)(tf.width * (c->floor_x - c->cell_x));
		c->ty = (int)(tf.height * (c->floor_y - c->cell_y));
		c->floor_x += c->floor_step_x;
		c->floor_y += c->floor_step_y;
		c->color = tex_get_pixel(&tf, c->tx, c->ty);
		tex_pixel_put(&c->buff, x, y, c->color);
		c->color = tex_get_pixel(&tc, c->tx, c->ty);
		tex_pixel_put(&c->buff, x, HEIGHT - y - 1, c->color);
	}
}

void	raycast_floor_ceiling(t_game *g, t_cam *c)
{
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		c->ray_dir_x_0 = c->dir_x - c->plane_x;
		c->ray_dir_y_0 = c->dir_y - c->plane_y;
		c->ray_dir_x_1 = c->dir_x + c->plane_x;
		c->ray_dir_y_1 = c->dir_y + c->plane_y;
		c->p = y - HEIGHT / 2;
		c->pos_z = 0.5 * HEIGHT;
		c->row_distance = c->pos_z / c->p;
		c->floor_step_x = c->row_distance * (c->ray_dir_x_1 - c->ray_dir_x_0) / WIDTH;
		c->floor_step_y = c->row_distance * (c->ray_dir_y_1 - c->ray_dir_y_0) / WIDTH;
		c->floor_x = g->p->x + c->row_distance * c->ray_dir_x_0;
		c->floor_y = g->p->y + c->row_distance * c->ray_dir_y_0;
		raycast_cell(g, c, y);
	}
}
