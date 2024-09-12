/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 08:46:26 by tgriblin          #+#    #+#             */
/*   Updated: 2024/09/12 09:35:26 by tgriblin         ###   ########.fr       */
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

void	load_assets_gui(t_game *g)
{
	g->tex[TEX_GUI_INV_00_0] = load_tex(g, "assets/gui/inv_00_0.xpm", 600, 450);
	g->tex[TEX_GUI_INV_00_1] = load_tex(g, "assets/gui/inv_00_1.xpm", 600, 450);
	g->tex[TEX_GUI_INV_10_0] = load_tex(g, "assets/gui/inv_10_0.xpm", 600, 450);
	g->tex[TEX_GUI_INV_10_1] = load_tex(g, "assets/gui/inv_10_1.xpm", 600, 450);
	g->tex[TEX_GUI_INV_01_0] = load_tex(g, "assets/gui/inv_01_0.xpm", 600, 450);
	g->tex[TEX_GUI_INV_01_1] = load_tex(g, "assets/gui/inv_01_1.xpm", 600, 450);
	g->tex[TEX_GUI_INV_11_0] = load_tex(g, "assets/gui/inv_11_0.xpm", 600, 450);
	g->tex[TEX_GUI_INV_11_1] = load_tex(g, "assets/gui/inv_11_1.xpm", 600, 450);
	g->tex[TEX_GUI_0] = load_tex(g, "assets/gui/0.xpm", 34, 60);
	g->tex[TEX_GUI_1] = load_tex(g, "assets/gui/1.xpm", 34, 60);
	g->tex[TEX_GUI_2] = load_tex(g, "assets/gui/2.xpm", 34, 60);
	g->tex[TEX_GUI_3] = load_tex(g, "assets/gui/3.xpm", 34, 60);
	g->tex[TEX_GUI_4] = load_tex(g, "assets/gui/4.xpm", 34, 60);
	g->tex[TEX_GUI_5] = load_tex(g, "assets/gui/5.xpm", 34, 60);
	g->tex[TEX_GUI_6] = load_tex(g, "assets/gui/6.xpm", 34, 60);
	g->tex[TEX_GUI_7] = load_tex(g, "assets/gui/7.xpm", 34, 60);
	g->tex[TEX_GUI_8] = load_tex(g, "assets/gui/8.xpm", 34, 60);
	g->tex[TEX_GUI_9] = load_tex(g, "assets/gui/9.xpm", 34, 60);
	g->tex[TEX_GUI_SEP] = load_tex(g, "assets/gui/sep.xpm", 17, 60);
	g->tex[TEX_GUI_MAPWALL] = load_tex(g, "assets/gui/minimap_wall.xpm", 10, 10);
	g->tex[TEX_GUI_MAPPLAYER] = load_tex(g, "assets/gui/minimap_player.xpm", 10, 10);
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
	g->tex[TEX_WALL_BRICKS] = load_tex(g, "assets/wall_bricks.xpm", 100, 100);
	g->tex[TEX_WALL_CLASS] = load_tex(g, "assets/wall_class.xpm", 100, 100);
	g->tex[TEX_BOARD_1] = load_tex(g, "assets/board_1.xpm", 100, 100);
	g->tex[TEX_BOARD_2] = load_tex(g, "assets/board_2.xpm", 100, 100);
	g->tex[TEX_BOARD_3] = load_tex(g, "assets/board_3.xpm", 100, 100);
	g->tex[TEX_FLOOR] = load_tex(g, "assets/floor.xpm", 100, 100);
	g->tex[TEX_CEILING] = load_tex(g, "assets/ceiling.xpm", 100, 100);
	load_assets_gui(g);
}
