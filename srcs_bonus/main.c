/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 08:09:01 by tgriblin          #+#    #+#             */
/*   Updated: 2024/09/10 09:39:01 by tgriblin         ###   ########.fr       */
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
	if (keycode == KEY_W || keycode == KEY_S)
		move_player(g, g->p->cam, keycode);
	if (keycode == KEY_A || keycode == KEY_D)
		move_player(g, g->p->cam, keycode);
	if (keycode == KEY_RIGHT || keycode == KEY_LEFT)
		rotate_player(g->p->cam, keycode);
	if (keycode == KEY_1 || keycode == KEY_2)
		switch_slots(g, keycode);
	//raycast(g, g->p->cam, -1);
	return (0);
}

int	mouse_click(int button, int x, int y, t_game *g)
{
	(void)x;
	(void)y;
	if (g->scene == 0 && button == LEFT_CLICK)
	{
		g->scene = 1;
		raycast(g, g->p->cam, -1);
		mlx_destroy_image(g->mlx, g->tmp_tex.ptr);
	}
	if (g->scene == 1 && (button == WHEEL_DOWN || button == WHEEL_UP))
	{
		if (get_time() - g->last_wheel > 1000)
		{
			g->last_wheel = get_time();
			if (g->curr_slot == 0)
				g->curr_slot = 1;
			else
				g->curr_slot = 0;
		}
	}
	//raycast(g, g->p->cam, -1);
	return (0);
}

/*int	mouse_move(int x, int y, t_game *g)
{
	int	move;

	(void)y;
	move = 0;

	//mlx_mouse_move(g->mlx, g->win, WIDTH / 2, HEIGHT / 2);
	if (x > WIDTH / 2)
		move = KEY_RIGHT;
	else if (x < WIDTH / 2)
		move = KEY_LEFT;
	if (move)
	{
		rotate_player(g->p->cam, move);
		raycast(g, g->p->cam, -1);
	}
	return (0);
}*/

int	load_map(t_game *g, char *path)
{
	int	i;

	if (parse_map_layout(g, path))
	{
		tab_free(g->map->content);
		free(g->map);
		return (put_error("Error while parsing the map!\n"));
	}
	/*if (check_map_bounds(g->map->content, 0))
	{
		tab_free(g->map->content);
		free(g->map);
		return (put_error("Error: map bounds must be walls!\n"));
	}*/
	g->map->sizes = malloc(g->map->height * sizeof(int));
	i = -1;
	while (g->map->content[++i])
		g->map->sizes[i] = ft_strlen(g->map->content[i]);
	return (check_map_chars(g->map->content));
}

int	main_loop(t_game *g)
{
	if (g->scene == 1)
		update_screen(g);
	return (0);
}

int	main(void)
{
	t_game		g;

	if (load_map(&g, "maps/bonus/f1.cub"))
		return (1);
	g.mlx = mlx_init();
	g.win = mlx_new_window(g.mlx, WIDTH, HEIGHT, GAME_TITLE);
	g.scene = 0;
	g.tmp_tex = load_tex(&g, "assets/loading_splash.xpm", 1200, 900);
	mlx_put_image_to_window(g.mlx, g.win, g.tmp_tex.ptr, 0, 0);
	load_assets(&g);
	init_values(&g);
	if (g.scene == 0)
		mlx_put_image_to_window(g.mlx, g.win, g.tex[TEX_MENU_BG].ptr, 0, 0);
	//mlx_mouse_move(g.mlx, g.win, WIDTH / 2, HEIGHT / 2);
	mlx_hook(g.win, 2, 1L << 0, key_pressed, &g);
	mlx_hook(g.win, 17, 0L, close_game, &g);
	mlx_hook(g.win, 4, 1L << 2, mouse_click, &g);
	mlx_loop_hook(g.mlx, main_loop, &g);
	//mlx_hook(g.win, 6, 1L << 6, mouse_move, &g);
	mlx_loop(g.mlx);
	return (0);
}
