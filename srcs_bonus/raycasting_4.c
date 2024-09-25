/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:39:20 by tgriblin          #+#    #+#             */
/*   Updated: 2024/09/25 16:21:35 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static int	get_texture_enemy(t_game *g, int i, int is_dead)
{
	int	type;

	type = g->enemies[i].type;
	if (type == STUDENT && is_dead)
		return (TEX_NPC_STUDENT_DEAD);
	if (type == BULLY && is_dead)
		return (TEX_NPC_BULLY_DEAD);
	if (type == STUDENT)
		return (TEX_NPC_STUDENT_F_0 + (get_time() % (2 * 250)) / 250);
	if (type == BULLY)
		return (TEX_NPC_BULLY_F_1 - (get_time() % (2 * 250)) / 250);
	if (type == NEXTBOT_1)
		return (TEX_NPC_JERAU);
	if (type == NEXTBOT_2)
		return (TEX_NPC_PIRATE_0 + (get_time() % (8 * 150)) / 150);
	if (type == NEXTBOT_3)
		return (TEX_NPC_POULET);
	return (TEX_WALL_BACKROOMS_0);
}

static void	raycast_enemy_draw(t_game *g, t_cam *c, int i)
{
	t_tex	tex;

	tex = g->tex[get_texture_enemy(g, i, g->enemies[i].is_dead)];
	c->pix_x = c->draw_x[0] - 1;
	while (c->pix_x++ < c->draw_x[1])
	{
		c->tex_x = (int)(256 * (c->pix_x - (-c->spr_w / 2 + c->spr_screen_x))
				* tex.width / c->spr_w) / 256;
		if (c->transf_y > 0 && c->transf_y < c->z_buffer[c->pix_x])
		{
			c->pix_y = c->draw_y[0] - 1;
			while (++c->pix_y < c->draw_y[1])
			{
				c->d = c->pix_y * 256 - HEIGHT * 128 + c->spr_h * 128;
				c->tex_y = ((c->d * tex.height) / c->spr_h) / 256;
				c->color = tex_get_pixel(&tex, c->tex_x, c->tex_y);
				tex_pixel_put(&c->buff, c->pix_x, c->pix_y, c->color);
			}
		}
	}
}

static void	raycast_enemy_calc(t_game *g, t_cam *c, int i)
{
	c->spr_x = g->enemies[i].x - g->p->x;
	c->spr_y = g->enemies[i].y - g->p->y;
	c->i_det = 1.0 / (c->plane_x * c->dir_y - c->dir_x * c->plane_y);
	c->transf_x = c->i_det
		* (c->dir_y * c->spr_x - c->dir_x * c->spr_y);
	c->transf_y = c->i_det
		* (-c->plane_y * c->spr_x + c->plane_x * c->spr_y);
	c->spr_screen_x = (int)((WIDTH / 2) * (1.0 + c->transf_x / c->transf_y));
	c->spr_h = abs((int)(HEIGHT / c->transf_y));
	c->draw_y[0] = -c->spr_h / 2 + HEIGHT / 2;
	if (c->draw_y[0] < 0)
		c->draw_y[0] = 0;
	c->draw_y[1] = c->spr_h / 2 + HEIGHT / 2;
	if (c->draw_y[1] > HEIGHT)
		c->draw_y[1] = HEIGHT;
	c->spr_w = abs((int)(HEIGHT / c->transf_y));
	c->draw_x[0] = -c->spr_w / 2 + c->spr_screen_x;
	if (c->draw_x[0] < 0)
		c->draw_x[0] = 0;
	c->draw_x[1] = c->spr_w / 2 + c->spr_screen_x;
	if (c->draw_x[1] > WIDTH)
		c->draw_x[1] = WIDTH;
	raycast_enemy_draw(g, c, i);
}

static void	raycast_enemy_sort(t_game *g)
{
	t_enemy	tmp;
	int		i;
	int		j;
	int		max;

	i = -1;
	while (++i < g->enemies_amt)
	{
		max = i;
		j = i;
		while (++j < g->enemies_amt)
			if (g->enemies[j].dist > g->enemies[max].dist)
				max = j;
		tmp = g->enemies[i];
		g->enemies[i] = g->enemies[max];
		g->enemies[max] = tmp;
	}
}

void	raycast_enemies(t_game *g, t_cam *c)
{
	double	t;
	int		i;

	i = -1;
	while (++i < g->enemies_amt)
	{
		t = dist_to_tile(g, g->enemies[i].x, g->enemies[i].y);
		g->enemies[i].dist = t;
	}
	raycast_enemy_sort(g);
	i = -1;
	while (++i < g->enemies_amt)
		raycast_enemy_calc(g, c, i);
}
