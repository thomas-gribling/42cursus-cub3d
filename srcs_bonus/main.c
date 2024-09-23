/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 08:09:01 by tgriblin          #+#    #+#             */
/*   Updated: 2024/09/23 09:30:05 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include "../include/cub3d_bonus.h"
#include "../include/gnl.h"

int	close_game(t_game *g)
{
	int	i;

	tab_free(g->map->content);
	free(g->map->sizes);
	free(g->map->spr);
	free(g->map);
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

int	key_pressed(int keycode, t_game *g)
{
	if (keycode == KEY_ESCAPE)
		close_game(g);
	if (g->scene != 1)
		return (0);
	if ((keycode == KEY_W || keycode == KEY_S) && !g->p->moving_x)
		g->p->moving_x = keycode;
	if ((keycode == KEY_A || keycode == KEY_D) && !g->p->moving_y)
		g->p->moving_y = keycode;
	if ((keycode == KEY_RIGHT || keycode == KEY_LEFT) && !g->p->rotating)
		g->p->rotating = keycode;
	if (keycode == KEY_1 || keycode == KEY_2)
		switch_slots(g, keycode);
	if (keycode == KEY_TAB)
		g->show_map = !g->show_map;
	return (0);
}

int	key_released(int keycode, t_game *g)
{
	if (g->scene != 1)
		return (0);
	if ((keycode == KEY_W || keycode == KEY_S) && g->p->moving_x)
		g->p->moving_x = 0;
	if ((keycode == KEY_A || keycode == KEY_D) && g->p->moving_y)
		g->p->moving_y = 0;
	if ((keycode == KEY_RIGHT || keycode == KEY_LEFT) && g->p->rotating)
		g->p->rotating = 0;
	return (0);
}

int	mouse_click(int button, int x, int y, t_game *g)
{
	(void)x;
	(void)y;
	if (g->scene == 0 && button == LEFT_CLICK)
	{
		g->scene = 1;
		g->start = get_time();
		g->last_frame = g->start;
		mlx_mouse_hide(g->mlx, g->win);
		raycast(g, g->p->cam, -1);
		mlx_destroy_image(g->mlx, g->tmp_tex.ptr);
	}
	if (g->scene == 1 && (button == WHEEL_DOWN || button == WHEEL_UP))
	{
		if (get_time() - g->last_wheel > 300.0)
		{
			g->last_wheel = get_time();
			g->curr_slot = !g->curr_slot;
		}
	}
	return (0);
}

int	mouse_move(int x, int y, t_game *g)
{
	int	move;

	(void)y;
	if (g->scene != 1)
		return (0);
	move = 0;
	if (x > g->mouse_middle_x || x > WIDTH - 11)
		move = KEY_RIGHT;
	else if (x < g->mouse_middle_x || x < 10)
		move = KEY_LEFT;
	if (move)
	{
		rotate_player(g->p->cam, move);
		g->mouse_middle_x = x;
		raycast(g, g->p->cam, -1);
	}
	return (0);
}

t_map	*load_map(char *path)
{
	int		i;
	t_map	*map;

	map = NULL;
	if (parse_map_layout(&map, path))
	{
		if (map)
			tab_free(map->content);
		free(map);
		return (put_error("Error while parsing the map!\n"), NULL);
	}
	map->sizes = malloc(map->height * sizeof(int));
	i = -1;
	while (map->content[++i])
		map->sizes[i] = ft_strlen(map->content[i]);
	read_spr(&map);
	return (map);
}

int	main_loop(t_game *g)
{
	int	pos[2];

	if (g->scene == 1)
	{
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
		if ((pos[0] < 10 || pos[0] > WIDTH - 11) && pos[0] >= 0 && pos[0] < WIDTH)
			mouse_move(pos[0], pos[1], g);
	}
	return (0);
}

int	main(void)
{
	t_game		g;

	g.map = load_map("maps/bonus/f1.cub");
	if (!g.map)
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
