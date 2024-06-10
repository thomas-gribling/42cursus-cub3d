/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 08:31:44 by tgriblin          #+#    #+#             */
/*   Updated: 2024/06/10 08:56:54 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include "../include/cub3d.h"

void	draw_square(t_game *g, int size, int posx, int posy)
{
	int	x;
	int	y;

	y = -1;
	while (++y < size)
	{
		x = -1;
		while (++x < size)
			mlx_pixel_put(g->mlx, g->win, x + 100 * posx, y + 100 * posy, 0xFFFFFF);

	}	
}

void	draw_map(t_game *g)
{
	int	x;
	int	y;

	y = -1;
	while (g->map->content[++y])
	{
		x = -1;
		while (g->map->content[y][++x])
			if (g->map->content[y][x] == '1')
				draw_square(g, 100, x, y);
	}
}

int	raycast(t_game *g)
{
	mlx_clear_window(g->mlx, g->win);
	draw_map(g);
	return (0);
}