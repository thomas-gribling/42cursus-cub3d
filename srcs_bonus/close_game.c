/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:53:37 by tgriblin          #+#    #+#             */
/*   Updated: 2024/10/10 11:55:17 by tgriblin         ###   ########.fr       */
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
