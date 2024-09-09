/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 10:43:01 by tgriblin          #+#    #+#             */
/*   Updated: 2024/09/09 08:52:18 by tgriblin         ###   ########.fr       */
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
}

static void	get_player_spawn_ew(t_game *g, int x, int y)
{
	char	c;

	c = g->map->content[y][x];
	if (c == 'E')
	{
		g->p->cam->dir_x = 1;
		g->p->cam->dir_y = 0;
		g->p->cam->plane_x = 0;
		g->p->cam->plane_y = 0.66;
	}
	if (c == 'W')
	{
		g->p->cam->dir_x = -1;
		g->p->cam->dir_y = 0;
		g->p->cam->plane_x = 0;
		g->p->cam->plane_y = -0.66;
	}
	g->p->x = x + 0.5;
	g->p->y = y + 0.5;
}

static void	get_player_spawn_ns(t_game *g, int x, int y)
{
	char	c;

	c = g->map->content[y][x];
	if (c == 'N')
	{
		g->p->cam->dir_x = 0;
		g->p->cam->dir_y = -1;
		g->p->cam->plane_x = 0.66;
		g->p->cam->plane_y = 0;
	}
	if (c == 'S')
	{
		g->p->cam->dir_x = 0;
		g->p->cam->dir_y = 1;
		g->p->cam->plane_x = -0.66;
		g->p->cam->plane_y = 0;
	}
	g->p->x = x + 0.5;
	g->p->y = y + 0.5;
}

void	init_values(t_game *g)
{
	int	x;
	int	y;

	g->p = malloc(sizeof(t_player));
	g->p->cam = malloc(sizeof(t_cam));
	y = -1;
	while (g->map->content[++y])
	{
		x = -1;
		while (g->map->content[y][++x])
		{
			if (g->map->content[y][x] == 'N' || g->map->content[y][x] == 'S')
				get_player_spawn_ns(g, x, y);
			if (g->map->content[y][x] == 'E' || g->map->content[y][x] == 'W')
				get_player_spawn_ew(g, x, y);
		}
	}
	g->p->cam->speed_m = 0.1;
	g->p->cam->speed_r = 0.033 * 1.8;
	g->p->cam->map_x = (int)g->p->x;
	g->p->cam->map_y = (int)g->p->y;
	g->p->cam->hit = 0;
	init_buffer(g);
}
