/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:04:43 by tgriblin          #+#    #+#             */
/*   Updated: 2024/09/26 10:07:21 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static void	generate_nextbots(t_game *g)
{
	int	i;

	g->bullies_amt = 0;
	g->enemies_amt = 3;
	g->enemies = malloc(g->enemies_amt * sizeof(t_enemy));
	i = -1;
	while (++i < g->enemies_amt)
	{
		g->enemies[i].type = NEXTBOT_1 + i;
		g->enemies[i].dist = 0.0;
		g->enemies[i].dirx = -1 + 2 * (rand() % 2);
		g->enemies[i].diry = -1 + 2 * (rand() % 2);
		g->enemies[i].is_dead = 0;
	}
	g->enemies[0].x = 107.5;
	g->enemies[0].y = 34.5;
	g->enemies[1].x = 20.5;
	g->enemies[1].y = 47.5;
	g->enemies[2].x = 75.5;
	g->enemies[2].y = 3.5;
}

static void	rand_pos(t_game *g, double *posx, double *posy)
{
	int		x;
	int		y;
	char	c;

	y = -1;
	*posx = 0.0;
	*posy = 0.0;
	while (g->map->content[++y] && !*posx)
	{
		x = -1;
		while (g->map->content[y][++x])
		{
			c = g->map->content[y][x];
			if (!is_collision(c) && !is_castable(c)
				&& rand() % (g->map->width * g->map->height / 2) == 0)
			{
				*posx = x + 0.5;
				*posy = y + 0.5;
			}
		}
	}
	if (!*posx)
		rand_pos(g, posx, posy);
}

static void	generate_one_enemy(t_game *g, int difficulty, int i)
{
	g->enemies[i].dist = 0.0;
	g->enemies[i].dirx = -1 + 2 * (rand() % 2);
	g->enemies[i].diry = -1 + 2 * (rand() % 2);
	if (rand() % (difficulty + 1) == 0)
		g->enemies[i].type = STUDENT;
	else
	{
		g->enemies[i].type = BULLY;
		g->bullies_amt++;
	}
	rand_pos(g, &g->enemies[i].x, &g->enemies[i].y);
	g->enemies[i].is_dead = 0;
}

void	generate_enemies(t_game *g, int difficulty)
{
	int	i;

	free_enemies(g);
	srand(rand() % get_time());
	if (difficulty == -1)
	{
		generate_nextbots(g);
		return ;
	}
	g->bullies_amt = 0;
	g->enemies_amt = 25 + rand() % (5 + difficulty * 5);
	g->enemies = malloc(g->enemies_amt * sizeof(t_enemy));
	i = -1;
	while (++i < g->enemies_amt)
		generate_one_enemy(g, difficulty, i);
}