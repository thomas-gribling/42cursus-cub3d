/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:13:14 by tgriblin          #+#    #+#             */
/*   Updated: 2024/09/26 09:13:44 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	is_portal(t_game *g, int x, int y)
{
	int		tex;
	int		curr_portal;
	int		dir;

	dir = get_dir(g->p->cam);
	curr_portal = -1;
	if (x == g->portals[0].map_x && y == g->portals[0].map_y
		&& g->portals[0].is_placed && g->portals[0].face == dir)
		curr_portal = 0;
	if (x == g->portals[1].map_x && y == g->portals[1].map_y
		&& g->portals[1].is_placed && g->portals[1].face == dir)
		curr_portal = 1;
	if (curr_portal == -1)
		return (0);
	tex = TEX_PORTAL_0 + curr_portal;
	return (tex);
}
