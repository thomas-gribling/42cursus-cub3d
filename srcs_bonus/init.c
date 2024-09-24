/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 10:43:01 by tgriblin          #+#    #+#             */
/*   Updated: 2024/09/24 15:44:29 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"
#include "../mlx/mlx.h"

static void	init_buffer(t_game *g)
{
	t_tex	*b;

	b = &g->p->cam->buff;
	b->ptr = mlx_new_image(g->mlx, WIDTH, HEIGHT);
	b->addr = mlx_get_data_addr(b->ptr, &b->bpp, &b->line_len, &b->endian);
	b->width = WIDTH;
	b->height = HEIGHT;
	g->curr_slot = 0;
	g->slots[0] = 0;
	g->slots[1] = 0;
	g->last_wheel = get_time();
	g->show_map = 0;
	g->last_frame = get_time();
	g->last_fps_update = get_time();
	g->fps = 1.0;
	g->p->moving_x = 0;
	g->p->moving_y = 0;
	g->p->rotating = 0;
}

static void	turn_player_to_bis(t_cam *c, int dir)
{
	if (dir == EAST)
	{
		c->dir_x = 1;
		c->dir_y = 0;
		c->plane_x = 0;
		c->plane_y = 0.66;
	}
	if (dir == WEST)
	{
		c->dir_x = -1;
		c->dir_y = 0;
		c->plane_x = 0;
		c->plane_y = -0.66;
	}
}

void	turn_player_to(t_cam *c, int dir)
{
	if (dir == NORTH)
	{
		c->dir_x = 0;
		c->dir_y = -1;
		c->plane_x = 0.66;
		c->plane_y = 0;
	}
	if (dir == SOUTH)
	{
		c->dir_x = 0;
		c->dir_y = 1;
		c->plane_x = -0.66;
		c->plane_y = 0;
	}
	turn_player_to_bis(c, dir);
}

void	init_values(t_game *g)
{
	g->curr_level = 0;
	g->p = malloc(sizeof(t_player));
	g->p->cam = malloc(sizeof(t_cam));
	g->mouse_middle_x = WIDTH / 2;
	tp_player_spawn(g);
	g->p->cam->speed_m = 0.1;
	g->p->cam->speed_r = 0.033 * 1.8 / 1.5;
	g->p->cam->map_x = (int)g->p->x;
	g->p->cam->map_y = (int)g->p->y;
	g->p->cam->hit = 0;
	g->p->cam->colls = NULL;
	g->portals[0].map_x = 16;
	g->portals[0].map_y = 4;
	g->portals[0].face = WEST;
	g->portals[0].is_placed = 1;
	g->portals[1].map_x = 16;
	g->portals[1].map_y = 6;
	g->portals[1].face = WEST;
	g->portals[1].is_placed = 1;
	init_buffer(g);
}
