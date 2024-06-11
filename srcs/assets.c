/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 08:46:26 by tgriblin          #+#    #+#             */
/*   Updated: 2024/06/11 10:18:02 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../mlx/mlx.h"

t_tex	load_tex(t_game *g, char *path, int width, int height)
{
	t_tex	s;

	s.width = width;
	s.height = height;
	s.bpp = 8;
	s.ptr = mlx_xpm_file_to_image(g->mlx, path, &s.width, &s.height);
	return (s);
}

void	load_assets(t_game *g)
{
	g->tex = malloc(TEX_AMT * sizeof(t_tex));
	g->tex[TEX_WALL] = load_tex(g, "assets/wall.xpm", 160, 160);
	g->tex[TEX_FLOOR] = load_tex(g, "assets/floor.xpm", 160, 160);
	g->tex[TEX_CEIL] = load_tex(g, "assets/ceil.xpm", 160, 160);
}
