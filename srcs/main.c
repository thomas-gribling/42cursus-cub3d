/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 08:09:01 by tgriblin          #+#    #+#             */
/*   Updated: 2024/06/10 08:22:24 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include "../include/cub3d.h"

int	close_game(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	mlx_loop_end(game->mlx);
	free(game->mlx);
	exit(0);
}

int	key_pressed(int keycode, t_game *game)
{
	if (keycode == KEY_ESCAPE)
		close_game(game);
	return (0);
}

int	main(int ac, char **av)
{
	t_game		g;

	(void)ac;
	(void)av;
	g.mlx = mlx_init();
	g.win = mlx_new_window(g.mlx, WIDTH, HEIGHT, GAME_TITLE);
	mlx_hook(g.win, 2, 1L << 0, key_pressed, &g);
	mlx_hook(g.win, 17, 0L, close_game, &g);
	mlx_loop(g.mlx);
	return (0);
}
