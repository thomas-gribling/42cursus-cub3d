/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 08:46:26 by tgriblin          #+#    #+#             */
/*   Updated: 2024/09/25 18:27:27 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_tex	load_tex(t_game *g, char *path)
{
	t_tex	s;

	s.ptr = mlx_xpm_file_to_image(g->mlx, path, &s.width, &s.height);
	s.addr = mlx_get_data_addr(s.ptr, &s.bpp, &s.line_len, &s.endian);
	return (s);
}

void	load_assets(t_game *g)
{
	g->tex = malloc(TEX_AMT * sizeof(t_tex));
	g->tex[TEX_WALL_N] = load_tex(g, g->tex_paths[0]);
	g->tex[TEX_WALL_E] = load_tex(g, g->tex_paths[3]);
	g->tex[TEX_WALL_S] = load_tex(g, g->tex_paths[1]);
	g->tex[TEX_WALL_W] = load_tex(g, g->tex_paths[2]);
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

void	reset_buffer(t_game *g, t_tex *buff)
{
	int	x;
	int	y;

	x = -1;
	while (++x < WIDTH)
	{
		y = -1;
		while (++y < HEIGHT)
			if ((int)tex_get_pixel(buff, x, y) != g->colors[y > HEIGHT / 2])
				tex_pixel_put(buff, x, y, g->colors[y > HEIGHT / 2]);
	}
}
