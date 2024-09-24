/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 08:09:01 by tgriblin          #+#    #+#             */
/*   Updated: 2024/09/24 15:26:18 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include "../include/cub3d_bonus.h"
#include "../include/gnl.h"

int	close_game(t_game *g)
{
	int	i;

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
	i = -1;
	while (++i < TEX_AMT)
		mlx_destroy_image(g->mlx, g->tex[i].ptr);
	free(g->tex);
	mlx_destroy_window(g->mlx, g->win);
	if (g->mlx)
		mlx_destroy_display(g->mlx);
	mlx_loop_end(g->mlx);
	free(g->mlx);
	exit(0);
}

int	main_loop(t_game *g)
{
	int	pos[2];

	if (g->scene == 1)
	{
		if (g->curr_level >= 0)
			update_screen(g);
		if (g->p->moving_x && g->p->moving_y)
			g->p->cam->speed_m = 0.05;
		else
			g->p->cam->speed_m = 0.1;
		if (g->p->moving_x)
			move_player(g, g->p->cam, g->p->moving_x);
		if (g->p->moving_y)
			move_player(g, g->p->cam, g->p->moving_y);
		if (g->p->rotating)
			rotate_player(g->p->cam, g->p->rotating);
		mlx_mouse_get_pos(g->mlx, g->win, &pos[0], &pos[1]);
		if ((pos[0] < 10 || pos[0] > WIDTH - 11) && pos[0] >= 0
			&& pos[0] < WIDTH)
			mouse_move(pos[0], pos[1], g);
	}
	return (0);
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
	load_assets(&g);
	init_values(&g);
	if (g.scene == 0)
		mlx_put_image_to_window(g.mlx, g.win, g.tex[TEX_MENU_BG].ptr, 0, 0);
	mlx_hook(g.win, 2, 1L << 0, key_pressed, &g);
	mlx_hook(g.win, 3, 1L << 1, key_released, &g);
	mlx_hook(g.win, 17, 0L, close_game, &g);
	mlx_hook(g.win, 4, 1L << 2, mouse_click, &g);
	mlx_hook(g.win, 6, 1L << 6, mouse_move, &g);
	mlx_loop_hook(g.mlx, main_loop, &g);
	mlx_loop(g.mlx);
	return (0);
}
