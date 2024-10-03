/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:22:53 by tgriblin          #+#    #+#             */
/*   Updated: 2024/10/03 15:11:29 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static int	has_ceiling(t_game *g, t_cam *c)
{
	if (g->map->content[c->cell_y][c->cell_x] != 'O'
		&& g->map->content[c->cell_y][c->cell_x] != 'G'
		&& g->map->content[c->cell_y][c->cell_x] != 'T'
		&& g->map->content[c->cell_y][c->cell_x] != 'S'
		&& g->map->content[c->cell_y][c->cell_x] != '9')
		return (1);
	return (0);
}

static int	get_floor_tex(t_game *g, t_cam *ca)
{
	char	c;

	c = g->map->content[ca->cell_y][ca->cell_x];
	if (g->curr_level == 3)
		return (TEX_CARPET);
	if (c == 'E' && g->curr_level == 0)
		return (TEX_FLOOR_TRAPDOOR);
	if (c == 'E' && g->curr_level == 1)
		return (TEX_GROUND_TRAPDOOR);
	if (c == 'O' || c == '9' || g->curr_level > 0)
		return (TEX_GROUND);
	if (c == 'S')
		return (TEX_GROUND_BACKROOMS);
	if (c == 'G' || c == 'T')
		return (TEX_GRASS);
	return (TEX_FLOOR);
}

static void	raycast_put_pixel(t_game *g, t_cam *c, int x, int y)
{
	t_tex	tf;
	t_tex	tc;

	if (c->cell_x >= 0 && c->cell_y >= 0
		&& c->cell_y < g->map->height && c->cell_x < g->map->sizes[c->cell_y]
		&& (!is_collision(g->map->content[c->cell_y][c->cell_x])
		|| is_transparent(g, g->map->content[c->cell_y][c->cell_x]) == 1))
	{
		tf = g->tex[get_floor_tex(g, c)];
		tc = g->tex[TEX_CEILING];
		if (g->curr_level == 1)
			tc = g->tex[TEX_CEILING_BSMT];
		if (g->curr_level == 2)
			tc = g->tex[TEX_GROUND];
		if (g->map->content[c->cell_y][c->cell_x] == 'F' && g->curr_level == 1)
			tc = g->tex[TEX_CEILINGBSMT];
		if (g->map->content[c->cell_y][c->cell_x] == 'F' && g->curr_level == 2)
			tc = g->tex[TEX_GROUND_TRAPDOOR];
		c->color = tex_get_pixel(&tf, c->tx[0], c->ty[0]);
		tex_pixel_put(&c->buff, x, y, c->color);
		c->color = tex_get_pixel(&tc, c->tx[1], c->ty[1]);
		if (has_ceiling(g, c))
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
	if (g->curr_level == 2)
		tc = g->tex[TEX_GROUND];
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
		c->floor_step_x = c->row_distance
			* (c->ray_dir_x_1 - c->ray_dir_x_0) / WIDTH;
		c->floor_step_y = c->row_distance
			* (c->ray_dir_y_1 - c->ray_dir_y_0) / WIDTH;
		c->floor_x = g->p->x + c->row_distance * c->ray_dir_x_0;
		c->floor_y = g->p->y + c->row_distance * c->ray_dir_y_0;
		raycast_cell(g, c, y);
	}
}
