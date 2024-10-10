/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 08:09:01 by tgriblin          #+#    #+#             */
/*   Updated: 2024/10/10 10:56:43 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	pre_init(t_game *g)
{
	g->colors[0] = 0;
	g->colors[1] = 0;
	g->tex_paths = NULL;
	g->f_found = 0;
	g->c_found = 0;
	g->dir_found[0] = 0;
	g->dir_found[1] = 0;
	g->dir_found[2] = 0;
	g->dir_found[3] = 0;
}

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
		if (g->tex[i].ptr)
			mlx_destroy_image(g->mlx, g->tex[i].ptr);
	free(g->tex);
	mlx_destroy_window(g->mlx, g->win);
	if (g->mlx)
		mlx_destroy_display(g->mlx);
	mlx_loop_end(g->mlx);
	free(g->mlx);
	exit(0);
}

int	load_map(t_game *g, char *path)
{
	pre_init(g);
	if (parse_map_infos(g, path, 0))
		return (put_error("Error while parsing map infos!\n"));
	if (parse_map_layout(g, path))
	{
		if (g->map)
			tab_free(g->map->content);
		free(g->map);
		return (put_error("Error while parsing map layout!\n"));
	}
	if (check_map_bounds(g->map->content, 0))
	{
		tab_free(g->map->content);
		free(g->map);
		return (put_error("Error: map bounds must be walls!\n"));
	}
	if (check_map_chars(g->map->content))
	{
		tab_free(g->map->content);
		free(g->map);
		return (1);
	}
	return (0);
}

int	main_loop(t_game *g)
{
	raycast(g, g->p->cam, -1);
	if (g->p->moving_x && g->p->moving_y)
		g->p->cam->speed_m = 0.025;
	else
		g->p->cam->speed_m = 0.05;
	if (g->p->moving_x)
		move_player(g, g->p->cam, g->p->moving_x);
	if (g->p->moving_y)
		move_player(g, g->p->cam, g->p->moving_y);
	if (g->p->rotating)
		rotate_player(g->p->cam, g->p->rotating);
	return (0);
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
	init_values(&g);
	if (load_assets(&g))
		return (put_error("Error while loading textures!\n"), close_game(&g));
	raycast(&g, g.p->cam, -1);
	mlx_hook(g.win, 2, 1L << 0, key_pressed, &g);
	mlx_hook(g.win, 3, 1L << 1, key_released, &g);
	mlx_hook(g.win, 17, 0L, close_game, &g);
	mlx_loop_hook(g.mlx, main_loop, &g);
	mlx_loop(g.mlx);
	return (0);
}
