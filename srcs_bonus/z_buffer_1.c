/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_buffer_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:29:57 by tgriblin          #+#    #+#             */
/*   Updated: 2024/09/25 19:57:13 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	fill_z_buffer(t_game *g)
{
	int	i;

	i = -1;
	free_z_buffer(g);
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
	int	i;

	if (g->z_buffer)
	{
		i = -1;
		while (++i < g->z_buffer_size)
			if (g->z_buffer[i].type == WALL)
				free(g->z_buffer[i].ptr);
		free(g->z_buffer);
		g->z_buffer = NULL;
		g->z_buffer_size = 0;
	}
}
