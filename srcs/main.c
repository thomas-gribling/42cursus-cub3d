/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 08:09:01 by tgriblin          #+#    #+#             */
/*   Updated: 2024/06/28 10:46:03 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include "../include/cub3d.h"

int	close_game(t_game *g)
{
	int	i;

	tab_free(g->map->content);
	free(g->map);
	tab_free(g->tex_paths);
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
	g->colors[0] = 0;
	g->colors[1] = 0;
	g->tex_paths = malloc(5 * sizeof(char *));
	g->tex_paths[4] = NULL;
	if (parse_map_infos(g, path))
		return (put_error("Error while parsing the map!\n"));
	if (parse_map_layout(g, path))
		return (put_error("Error while parsing the map!\n"));
	if (check_map_bounds(g->map->content, 0))
		return (put_error("Error: map bounds must be walls!\n"));
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
		return (tab_free(g.tex_paths), 1);
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
