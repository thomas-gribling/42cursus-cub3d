/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:39:20 by tgriblin          #+#    #+#             */
/*   Updated: 2024/09/25 17:34:07 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static void	raycast_spr_draw(t_cam *c, t_tex tex)
{
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

static void	raycast_spr_calc(t_cam *c, t_tex tex)
{
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
	raycast_spr_draw(c, tex);
}


void	raycast_sprite(t_game *g, t_cam *c, int i)
{
	t_sprite	*t;
	t_tex		tex;
	
	t = (t_sprite *)g->z_buffer[i].ptr;
	c->spr_x = t->x - g->p->x;
	c->spr_y = t->y - g->p->y;
	tex = g->tex[t->tex_id];
	raycast_spr_calc(c, tex);
}
