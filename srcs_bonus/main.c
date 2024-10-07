/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 08:09:01 by tgriblin          #+#    #+#             */
/*   Updated: 2024/10/07 15:21:42 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static int	close_game_bis(t_game *g)
{
	int	i;

	i = -1;
	while (++i < TEX_AMT)
		mlx_destroy_image(g->mlx, g->tex[i].ptr);
	free(g->tex);
	mlx_destroy_window(g->mlx, g->win);
	if (g->mlx)
		mlx_destroy_display(g->mlx);
	mlx_loop_end(g->mlx);
	free(g->mlx);
	return (0);
}

int	close_game(t_game *g)
{
	int	i;

	stopallsounds(g);
	free_z_buffer(g);
	i = -1;
	while (g->maps[++i])
	{
		tab_free(g->maps[i]->content);
		free(g->maps[i]->sizes);
		free(g->maps[i]->spr);
		free(g->maps[i]);
	}
	if (g->scene == 0)
		mlx_destroy_image(g->mlx, g->tmp_tex.ptr);
	mlx_destroy_image(g->mlx, g->p->cam->buff.ptr);
	free(g->p->cam);
	free(g->p);
	if (g->enemies)
		free(g->enemies);
	exit(close_game_bis(g));
}

static int	main_loop_bis(t_game *g)
{
	t_tex	*b;

	b = &g->p->cam->buff;
	if (g->scene == 0)
	{
		reset_buffer(b);
		tex_put_scale(b, &g->tex[TEX_MENU_BG], 0, 0);
		mlx_put_image_to_window(g->mlx, g->win, b->ptr, 0, 0);
	}
	if (g->scene == 1)
	{
		if (COPS_TIMER - (int)((get_time() - g->start) / 1000) + g->time_m < 1)
		{
			g->ending = 1 + g->curr_level;
			g->scene = 2;
		}
	}
	if (g->scene == 2)
	{
		reset_buffer(b);
		tex_put_scale(b, &g->tex[TEX_END_0_BG + g->ending], 0, 0);
		mlx_put_image_to_window(g->mlx, g->win, b->ptr, 0, 0);
		draw_credits(g);
	}
	return (0);
}

int	main_loop(t_game *g)
{
	int	pos[2];

	if (g->loop_start && get_time() - g->loop_start >= g->loop_time)
	{
		playsound(g->looped_snd, 0, 0, 0);
		g->loop_start = get_time();
	}
	if (g->scene == 1)
	{
		update_enemies(g);
		update_screen(g);
		if (g->curr_level == 2)
			update_chad(g);
		if (g->p->moving_x && g->p->moving_y)
			g->p->cam->speed_m = 0.05;
		else
			g->p->cam->speed_m = 0.1;
		if (g->p->moving_x)
			move_player(g, g->p->cam, g->p->moving_x);
		if (g->p->moving_y)
			move_player(g, g->p->cam, g->p->moving_y);
		if (g->p->rotating)
			rotate_player(g, g->p->cam, g->p->rotating);
		mlx_mouse_get_pos(g->mlx, g->win, &pos[0], &pos[1]);
		if ((pos[0] < 10 || pos[0] > WIDTH - 11) && pos[0] >= 0
			&& pos[0] < WIDTH)
			mouse_move(pos[0], pos[1], g);
	}
	return (main_loop_bis(g));
}

int	main(void)
{
	t_game		g;

	g.maps[0] = load_map("maps/bonus/lvl1.cub");
	g.maps[1] = load_map("maps/bonus/lvl2.cub");
	g.maps[2] = load_map("maps/bonus/lvl3.cub");
	g.maps[3] = load_map("maps/bonus/backrooms.cub");
	g.maps[4] = NULL;
	g.map = g.maps[0];
	if (!g.maps[0] || !g.maps[1] || !g.maps[2] || !g.maps[3])
		return (1);
	g.mlx = mlx_init();
	g.win = mlx_new_window(g.mlx, WIDTH, HEIGHT, GAME_TITLE);
	g.scene = 0;
	g.tmp_tex = load_tex(&g, "assets/loading_splash.xpm");
	mlx_put_image_to_window(g.mlx, g.win, g.tmp_tex.ptr, 0, 0);
	playsound(SND_SHOOT, 0, 0, 0);
	load_assets(&g);
	init_values(&g);
	playsoundloop(&g, MUS_MENU, MUS_MENU_DUR);
	do_hooks(&g);
	mlx_loop(g.mlx);
	return (0);
}
