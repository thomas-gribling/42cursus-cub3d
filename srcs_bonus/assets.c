/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 08:46:26 by tgriblin          #+#    #+#             */
/*   Updated: 2024/07/01 16:04:22 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"
#include "../mlx/mlx.h"

t_tex	load_tex(t_game *g, char *path, int width, int height)
{
	t_tex	s;

	s.width = width;
	s.height = height;
	s.ptr = mlx_xpm_file_to_image(g->mlx, path, &s.width, &s.height);
	s.addr = mlx_get_data_addr(s.ptr, &s.bpp, &s.line_len, &s.endian);
	return (s);
}

void	load_assets(t_game *g)
{
	g->tex = malloc(TEX_AMT * sizeof(t_tex));
	g->tex[TEX_WALL] = load_tex(g, "assets/wall.xpm", 100, 100);
	g->tex[TEX_DOOR] = load_tex(g, "assets/door.xpm", 100, 100);
	g->tex[TEX_WINDOW] = load_tex(g, "assets/window.xpm", 100, 100);
	g->tex[TEX_FLOOR] = load_tex(g, "assets/jerau.xpm", 100, 100);
	g->tex[TEX_CEILING] = load_tex(g, "assets/jerau.xpm", 100, 100);
	g->tex[TEX_NB_JERAU] = load_tex(g, "assets/jerau.xpm", 100, 100);
}

void	tex_pixel_put(t_tex *tex, int x, int y, int color)
{
	char	*pixel;

	pixel = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	*(int *)pixel = color;
}

unsigned int	tex_get_pixel(t_tex *tex, int x, int y)
{
	char	*pixel;

	pixel = tex->addr + (y * tex->line_len) + (x * tex->bpp / 8);
	return (*(unsigned int *)pixel);
}

void	reset_buffer(t_tex *buff)
{
	int	x;
	int	y;

	x = -1;
	while (++x < WIDTH)
	{
		y = -1;
		while (++y < HEIGHT)
			tex_pixel_put(buff, x, y, 0x000000);
	}
}
