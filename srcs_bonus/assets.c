/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 08:46:26 by tgriblin          #+#    #+#             */
/*   Updated: 2024/09/09 08:43:53 by tgriblin         ###   ########.fr       */
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
	g->tex[TEX_MENU_BG] = load_tex(g, "assets/menu_bg.xpm", 1200, 900);
	g->tex[TEX_WALL] = load_tex(g, "assets/wall.xpm", 100, 100);
	g->tex[TEX_WALL_SIGN] = load_tex(g, "assets/wall_sign.xpm", 100, 100);
	g->tex[TEX_DOOR_C] = load_tex(g, "assets/door_c.xpm", 100, 100);
	g->tex[TEX_DOOR_O] = load_tex(g, "assets/door_o.xpm", 100, 100);
	g->tex[TEX_WINDOW] = load_tex(g, "assets/window.xpm", 100, 100);
	g->tex[TEX_WALL_CLASS] = load_tex(g, "assets/wall_class.xpm", 100, 100);
	g->tex[TEX_BOARD_1] = load_tex(g, "assets/board_1.xpm", 100, 100);
	g->tex[TEX_BOARD_2] = load_tex(g, "assets/board_2.xpm", 100, 100);
	g->tex[TEX_BOARD_3] = load_tex(g, "assets/board_3.xpm", 100, 100);
	g->tex[TEX_FLOOR] = load_tex(g, "assets/floor.xpm", 100, 100);
	g->tex[TEX_CEILING] = load_tex(g, "assets/ceiling.xpm", 100, 100);
	g->tex[TEX_GUI_INV_00_0] = load_tex(g, "assets/gui/inv_00_0.xpm", 1200, 900);
	g->tex[TEX_GUI_INV_00_1] = load_tex(g, "assets/gui/inv_00_1.xpm", 1200, 900);
	g->tex[TEX_GUI_INV_10_0] = load_tex(g, "assets/gui/inv_10_0.xpm", 1200, 900);
	g->tex[TEX_GUI_INV_10_1] = load_tex(g, "assets/gui/inv_10_1.xpm", 1200, 900);
	g->tex[TEX_GUI_INV_01_0] = load_tex(g, "assets/gui/inv_01_0.xpm", 1200, 900);
	g->tex[TEX_GUI_INV_01_1] = load_tex(g, "assets/gui/inv_01_1.xpm", 1200, 900);
	g->tex[TEX_GUI_INV_11_0] = load_tex(g, "assets/gui/inv_11_0.xpm", 1200, 900);
	g->tex[TEX_GUI_INV_11_1] = load_tex(g, "assets/gui/inv_11_1.xpm", 1200, 900);
}

void	tex_tex_put(t_tex *to, t_tex *from, int x, int y)
{
	int		y_save;
	int		from_x;
	int		from_y;
	double	coeff[2];

	x -= 1;
	y_save = y - 1;
	from_x = -1;
	from_y = -1;
	coeff[0] = (double)from->width / (double)to->width;
	coeff[1] = (double)from->height / (double)to->height;
	while (++x < to->width)
	{
		from_x++;
		from_y = -1;
		y = y_save;
		while (++y < to->height)
		{
			from_y++;
			tex_pixel_put(to, x, y, tex_get_pixel(from, from_x * coeff[0], from_y * coeff[1]));
		}
	}
}

void	tex_pixel_put(t_tex *tex, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || x >= tex->width || y < 0 || y > tex->height)
		return ;
	pixel = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	if (color != 0xFF00FF)
		*(int *)pixel = color;
}

unsigned int	tex_get_pixel(t_tex *tex, int x, int y)
{
	char	*pixel;

	if (x < 0 || x >= tex->width || y < 0 || y > tex->height)
		return (0x000000);
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
		{
			if (y < HEIGHT / 2 && tex_get_pixel(buff, x, y) != 0x6AC9FB)
				tex_pixel_put(buff, x, y, 0x6AC9FB);
			if (y >= HEIGHT / 2 && tex_get_pixel(buff, x, y) != 0x00DD00)
				tex_pixel_put(buff, x, y, 0x00DD00);
		}
	}
}
