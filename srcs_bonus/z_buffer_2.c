/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_buffer_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:22:01 by tgriblin          #+#    #+#             */
/*   Updated: 2024/09/25 18:26:29 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static void	calc_dist_z_buffer(t_game *g)
{
	t_sprite	*t1;
	t_enemy		*t2;
	int			i;

	i = -1;
	while (++i < g->z_buffer_size)
	{
		if (g->z_buffer[i].type == SPRITE)
		{
			t1 = (t_sprite *)g->z_buffer[i].ptr;
			t1->dist = dist_to_tile(g, t1->x, t1->y);
		}
		if (g->z_buffer[i].type == ENEMY)
		{
			t2 = (t_enemy *)g->z_buffer[i].ptr;
			t2->dist = dist_to_tile(g, t2->x, t2->y);
		}
	}
}

static double	get_dist_z_buffer(t_game *g, int i)
{
	t_sprite	*t1;
	t_enemy		*t2;
	
	if (g->z_buffer[i].type == SPRITE)
	{
		t1 = (t_sprite *)g->z_buffer[i].ptr;
		return (t1->dist);
	}
	if (g->z_buffer[i].type == ENEMY)
	{
		t2 = (t_enemy *)g->z_buffer[i].ptr;
		return (t2->dist);
	}
	return (0.0);
}

static void	sort_z_buffer(t_game *g)
{
	t_actor	tmp;
	int		i;
	int		j;
	int		max;

	calc_dist_z_buffer(g);
	i = -1;
	while (++i < g->z_buffer_size)
	{
		max = i;
		j = i;
		while (++j < g->z_buffer_size)
		{
			if (get_dist_z_buffer(g, j) > get_dist_z_buffer(g, max))
				max = j;
		}
		tmp = g->z_buffer[i];
		g->z_buffer[i] = g->z_buffer[max];
		g->z_buffer[max] = tmp;
	}
}

void	raycast_z_buffer(t_game *g)
{
	int	i;

	i = -1;
	sort_z_buffer(g);
	while (++i < g->z_buffer_size)
	{
		if (g->z_buffer[i].type == SPRITE)
			raycast_sprite(g, g->p->cam, i);
		if (g->z_buffer[i].type == ENEMY)
			raycast_enemy(g, g->p->cam, i);
	}
}
