/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_raycasting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 08:32:04 by tgriblin          #+#    #+#             */
/*   Updated: 2024/09/16 11:18:51 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	is_collision(char c)
{
	if (c >= '1' && c <= '9')
		return (1);
	if (c == 'A')
		return (1);
	return (0);
}

int	is_transparent(char c)
{
	if (c == '3' || c == '4')
		return (1);
	return (0);
}

int	is_bounds(t_game *g, int x, int y)
{
	t_map	*map;

	map = g->map;
	if (x <= 0 || y <= 0 || y >= map->height || x >= map->sizes[y])
		return (1);
	return (0);
}

t_coll	*append_colls(t_coll *old, t_cam *c)
{
	t_coll	*new;
	int		i;

	i = 0;
	if (!old)
		new = malloc(sizeof(t_coll));
	else
	{
		new = malloc((c->colls_amt + 1) * sizeof(t_coll));
		i = -1;
		while (++i < c->colls_amt)
		{
			new[i].map_x = old[i].map_x;
			new[i].map_y = old[i].map_y;
			new[i].side = old[i].side;
		}
	}
	new[i].map_x = c->map_x;
	new[i].map_y = c->map_y;
	new[i].side = c->side;
	c->colls_amt++;
	free(old);
	return (new);
}

void	raycast_step(t_cam *c)
{
	if (c->side_dist_x < c->side_dist_y)
	{
		c->side_dist_x += c->delta_x;
		c->map_x += c->step_x;
		c->side = 0;
	}
	else
	{
		c->side_dist_y += c->delta_y;
		c->map_y += c->step_y;
		c->side = 1;
	}
}
