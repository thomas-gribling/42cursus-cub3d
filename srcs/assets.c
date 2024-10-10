/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 08:46:26 by tgriblin          #+#    #+#             */
/*   Updated: 2024/10/10 10:29:28 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	load_tex(t_game *g, char *path, int id)
{
	t_tex	s;

	s.ptr = mlx_xpm_file_to_image(g->mlx, path, &s.width, &s.height);
	if (s.ptr)
		s.addr = mlx_get_data_addr(s.ptr, &s.bpp, &s.line_len, &s.endian);
	g->tex[id] = s;
	return (!s.ptr);
}

int	load_assets(t_game *g)
{
	int	error;
	
	error = 0;
	g->tex = malloc(TEX_AMT * sizeof(t_tex));
	error += load_tex(g, g->tex_paths[0], TEX_WALL_N);
	error += load_tex(g, g->tex_paths[1], TEX_WALL_S);
	error += load_tex(g, g->tex_paths[2], TEX_WALL_W);
	error += load_tex(g, g->tex_paths[3], TEX_WALL_E);
	return (error);
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
