/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:39:20 by tgriblin          #+#    #+#             */
/*   Updated: 2024/09/18 19:39:36 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static void	raycast_spr_sort(t_game *g)
{
	t_sprite	tmp;
	int			i;
	int			j;
	int			max;

	i = -1;
	while (++i < g->map->spr_amt)
	{
		max = i;
		j = i;
		while (++j < g->map->spr_amt)
			if (g->map->spr[j].dist > g->map->spr[max].dist)
				max = j;
		tmp = g->map->spr[i];
		g->map->spr[i] = g->map->spr[max];
		g->map->spr[max] = tmp;
	}
	
}

void	raycast_sprites(t_game *g, t_cam *c)
{
	int	i;
	
	i = -1;
	while (++i < g->map->spr_amt)
		g->map->spr[i].dist = dist_to_tile(g, (int)floor(g->map->spr[i].x), (int)floor(g->map->spr[i].y));
	raycast_spr_sort(g);
	i = -1;
	while (++i < g->map->spr_amt)
	{
		double	sprite_x = g->map->spr[i].x - g->p->x;
		double	sprite_y = g->map->spr[i].y - g->p->y;

		double	inv_det = 1.0 / (c->plane_x * c->dir_y - c->dir_x * c->plane_y);
		
		double	transform_x = inv_det * (c->dir_y * sprite_x - c->dir_x * sprite_y);
		double	transform_y = inv_det * (-c->plane_y * sprite_x + c->plane_x * sprite_y);

		int	sprite_screen_x = (int)((WIDTH / 2) * (1.0 + transform_x / transform_y));

		int	sprite_h = abs((int)(HEIGHT / transform_y));
		int	draw_start_y = -sprite_h / 2 + HEIGHT / 2;
		if (draw_start_y < 0)
			draw_start_y = 0;
		int	draw_end_y = sprite_h / 2 + HEIGHT / 2;
		if (draw_end_y >= HEIGHT)
			draw_end_y = HEIGHT - 1;
		
		int	sprite_w = abs((int)(HEIGHT / transform_y));
		int	draw_start_x = -sprite_w / 2 + sprite_screen_x;
		if (draw_start_x < 0)
			draw_start_x = 0;
		int	draw_end_x = sprite_w / 2 + sprite_screen_x;
		if (draw_end_x >= WIDTH)
			draw_end_x = WIDTH - 1;
		
		int	stripe = draw_start_x - 1;
		while (stripe++ < draw_end_x)
		{
			t_tex	tex = g->tex[g->map->spr[i].tex_id];
			int	tex_x = (int)(256 * (stripe - (-sprite_w / 2 + sprite_screen_x)) * tex.width / sprite_w) / 256;
			if (transform_y > 0 && transform_y < c->z_buffer[stripe])
			{
				int	y = draw_start_y - 1;
				while (++y < draw_end_y)
				{
					int	d = y * 256 - HEIGHT * 128 + sprite_h * 128;
					int	tex_y = ((d * tex.height) / sprite_h) / 256;
					int	color = tex_get_pixel(&tex, tex_x, tex_y);
					tex_pixel_put(&c->buff, stripe, y, color);
				}
			}
		}
	}
}
