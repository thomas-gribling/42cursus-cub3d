/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 08:09:01 by tgriblin          #+#    #+#             */
/*   Updated: 2024/06/10 08:57:07 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include "../include/cub3d.h"

int	close_game(t_game *g)
{
	//tab_free(g->map->content);
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
	raycast(g);
	return (0);
}

int	main(int ac, char **av)
{
	t_game		g;

	(void)ac;
	(void)av;
	g.mlx = mlx_init();
	g.win = mlx_new_window(g.mlx, WIDTH, HEIGHT, GAME_TITLE);
	g.map = malloc(sizeof(t_map)); // temporary
	g.map->content = malloc(7 * sizeof(char *));
	g.map->content[0] = "1111111111";
	g.map->content[1] = "1P00000001";
	g.map->content[2] = "1001000001";
	g.map->content[3] = "1000001001";
	g.map->content[4] = "1000000001";
	g.map->content[5] = "1111111111";
	g.map->content[6] = NULL;
	raycast(&g);
	mlx_hook(g.win, 2, 1L << 0, key_pressed, &g);
	mlx_hook(g.win, 17, 0L, close_game, &g);
	mlx_loop(g.mlx);
	return (0);
}
