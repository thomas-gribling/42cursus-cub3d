/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_buffer_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:29:57 by tgriblin          #+#    #+#             */
/*   Updated: 2024/09/25 17:45:24 by tgriblin         ###   ########.fr       */
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

void	sort_z_buffer(t_game *g)
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

void	fill_z_buffer(t_game *g)
{
	int	i;

	i = -1;
	while (++i < g->map->spr_amt)
	{
		g->map->spr[i].tex_id = get_texture_spr(g, g->map->spr[i]);
		append_z_buffer(g, (void *)&g->map->spr[i], SPRITE);
	}
	i = -1;
	while (++i < g->enemies_amt)
		append_z_buffer(g, (void *)&g->enemies[i], ENEMY);
}

void	append_z_buffer(t_game *g, void *ptr, int type)
{
	t_actor	*new;
	int		i;
	
	i = 0;
	new = malloc((g->z_buffer_size + 1) * sizeof(t_actor));
	if (g->z_buffer)
	{
		i = -1;
		while (++i < g->z_buffer_size)
		{
			new[i].type = g->z_buffer[i].type;
			new[i].ptr = g->z_buffer[i].ptr;
		}
	}
	new[i].type = type;
	new[i].ptr = ptr;
	if (g->z_buffer)
		free(g->z_buffer);
	g->z_buffer_size++;
	g->z_buffer = new;
}

void	free_z_buffer(t_game *g)
{
	if (g->z_buffer)
	{
		free(g->z_buffer);
		g->z_buffer = NULL;
		g->z_buffer_size = 0;
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
