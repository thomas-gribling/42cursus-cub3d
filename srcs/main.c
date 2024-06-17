/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 08:09:01 by tgriblin          #+#    #+#             */
/*   Updated: 2024/06/17 11:14:13 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include "../include/cub3d.h"

int	close_game(t_game *g)
{
	int	i;

	//tab_free(g->map->content); // not possible for now
	free(g->map->content);
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

void	init_buffer(t_game *g)
{
	t_tex	*b;

	b = &g->p->cam->buff;
	b->ptr = mlx_new_image(g->mlx, WIDTH, HEIGHT);
	b->addr = mlx_get_data_addr(b->ptr, &b->bpp, &b->line_len, &b->endian);
}

void	init_player(t_game *g)
{
	g->p = malloc(sizeof(t_player));
	g->p->cam = malloc(sizeof(t_cam));
	g->p->x = 5;
	g->p->y = 5;
	g->p->cam->dir_x = -1;
	g->p->cam->dir_y = 0;
	g->p->cam->plane_x = 0;
	g->p->cam->plane_y = 0.66;
	g->p->cam->speed_m = 0.1;
	g->p->cam->speed_r = 0.033 * 1.8;
	g->p->cam->map_x = (int)g->p->x;
	g->p->cam->map_y = (int)g->p->y;
	g->p->cam->hit = 0;
	g->colors[0] = 0xF3F462; // will be taken directly from map
	g->colors[1] = 0x62F4AC;
	init_buffer(g);
}

int	main(int ac, char **av)
{
	t_game		g;

	(void)ac;
	(void)av;
	g.mlx = mlx_init();
	g.win = mlx_new_window(g.mlx, WIDTH, HEIGHT, GAME_TITLE);
	g.map = malloc(sizeof(t_map)); // temporary
	g.map->content = malloc(11 * sizeof(char *));
	g.map->content[0] = "1111111111";
	g.map->content[1] = "1000000111";
	g.map->content[2] = "1010000011";
	g.map->content[3] = "1000000001";
	g.map->content[4] = "1000000001";
	g.map->content[5] = "1000000001";
	g.map->content[6] = "1000000001";
	g.map->content[7] = "1100000011";
	g.map->content[8] = "1110000111";
	g.map->content[9] = "1111111111";
	g.map->content[10] = NULL;
	g.map->width = 10;
	g.map->height = 10;
	load_assets(&g);
	init_player(&g);
	raycast(&g, g.p->cam);
	mlx_hook(g.win, 2, 1L << 0, key_pressed, &g);
	mlx_hook(g.win, 17, 0L, close_game, &g);
	mlx_loop(g.mlx);
	return (0);
}
