/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 08:09:01 by tgriblin          #+#    #+#             */
/*   Updated: 2024/07/01 15:20:02 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include "../include/cub3d_bonus.h"

int	close_game(t_game *g)
{
	int	i;

	tab_free(g->map->content);
	free(g->map);
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
	if (keycode == KEY_W || keycode == KEY_S)
		move_player(g, g->p->cam, keycode);
	if (keycode == KEY_A || keycode == KEY_D)
		move_player(g, g->p->cam, keycode);
	if (keycode == KEY_RIGHT || keycode == KEY_LEFT)
		rotate_player(g->p->cam, keycode);
	raycast(g, g->p->cam, -1);
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
	return (check_map_chars(g->map->content));
}

int	main(void)
{
	t_game		g;

	if (load_map(&g, "maps/bonus/test.cub"))
		return (1);
	g.mlx = mlx_init();
	g.win = mlx_new_window(g.mlx, WIDTH, HEIGHT, GAME_TITLE);
	load_assets(&g);
	init_values(&g);
	raycast(&g, g.p->cam, -1);
	mlx_mouse_move(g.mlx, g.win, WIDTH / 2, HEIGHT / 2);
	mlx_hook(g.win, 2, 1L << 0, key_pressed, &g);
	mlx_hook(g.win, 17, 0L, close_game, &g);
	//mlx_hook(g.win, 6, 1L << 6, mouse_move, &g);
	mlx_loop(g.mlx);
	return (0);
}
