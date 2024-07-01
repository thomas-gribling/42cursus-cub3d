/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 08:09:01 by tgriblin          #+#    #+#             */
/*   Updated: 2024/07/01 12:12:04 by tgriblin         ###   ########.fr       */
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
	if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		rotate_player(g->p->cam, keycode);
	raycast(g, g->p->cam);
	return (0);
}

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

int	main(int ac, char **av)
{
	t_game		g;

	if (ac != 2)
		return (put_error("Arguments error!\nUsage: ./cub3d <map.cub>\n"));
	if (check_map_format(av[1]))
		return (put_error("Map is not a .cub file!\n"));
	if (load_map(&g, av[1]))
		return (1);
	g.mlx = mlx_init();
	g.win = mlx_new_window(g.mlx, WIDTH, HEIGHT, GAME_TITLE);
	load_assets(&g);
	init_values(&g);
	raycast(&g, g.p->cam);
	mlx_hook(g.win, 2, 1L << 0, key_pressed, &g);
	mlx_hook(g.win, 17, 0L, close_game, &g);
	mlx_loop(g.mlx);
	return (0);
}
