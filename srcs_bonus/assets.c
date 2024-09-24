/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 08:46:26 by tgriblin          #+#    #+#             */
/*   Updated: 2024/09/24 09:41:35 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"
#include "../mlx/mlx.h"

t_tex	load_tex(t_game *g, char *path)
{
	t_tex	s;

	s.ptr = mlx_xpm_file_to_image(g->mlx, path, &s.width, &s.height);
	s.addr = mlx_get_data_addr(s.ptr, &s.bpp, &s.line_len, &s.endian);
	return (s);
}

void	load_assets_gui(t_game *g)
{
	g->tex[TEX_GUI_INV_00_0] = load_tex(g, "assets/gui/inv_00_0.xpm");
	g->tex[TEX_GUI_INV_00_1] = load_tex(g, "assets/gui/inv_00_1.xpm");
	g->tex[TEX_GUI_INV_10_0] = load_tex(g, "assets/gui/inv_10_0.xpm");
	g->tex[TEX_GUI_INV_10_1] = load_tex(g, "assets/gui/inv_10_1.xpm");
	g->tex[TEX_GUI_INV_01_0] = load_tex(g, "assets/gui/inv_01_0.xpm");
	g->tex[TEX_GUI_INV_01_1] = load_tex(g, "assets/gui/inv_01_1.xpm");
	g->tex[TEX_GUI_INV_11_0] = load_tex(g, "assets/gui/inv_11_0.xpm");
	g->tex[TEX_GUI_INV_11_1] = load_tex(g, "assets/gui/inv_11_1.xpm");
	g->tex[TEX_GUI_0] = load_tex(g, "assets/gui/0.xpm");
	g->tex[TEX_GUI_1] = load_tex(g, "assets/gui/1.xpm");
	g->tex[TEX_GUI_2] = load_tex(g, "assets/gui/2.xpm");
	g->tex[TEX_GUI_3] = load_tex(g, "assets/gui/3.xpm");
	g->tex[TEX_GUI_4] = load_tex(g, "assets/gui/4.xpm");
	g->tex[TEX_GUI_5] = load_tex(g, "assets/gui/5.xpm");
	g->tex[TEX_GUI_6] = load_tex(g, "assets/gui/6.xpm");
	g->tex[TEX_GUI_7] = load_tex(g, "assets/gui/7.xpm");
	g->tex[TEX_GUI_8] = load_tex(g, "assets/gui/8.xpm");
	g->tex[TEX_GUI_9] = load_tex(g, "assets/gui/9.xpm");
	g->tex[TEX_GUI_SEP] = load_tex(g, "assets/gui/sep.xpm");
	g->tex[TEX_GUI_MAPWALL] = load_tex(g, "assets/gui/minimap_wall.xpm");
	g->tex[TEX_GUI_MAPPLAYER] = load_tex(g, "assets/gui/minimap_player.xpm");
}

void	load_assets(t_game *g)
{
	g->tex = malloc(TEX_AMT * sizeof(t_tex));
	g->tex[TEX_MENU_BG] = load_tex(g, "assets/menu_bg.xpm");
	g->tex[TEX_WALL] = load_tex(g, "assets/wall.xpm");
	g->tex[TEX_WALL_SIGN] = load_tex(g, "assets/wall_sign.xpm");
	g->tex[TEX_DOOR_C] = load_tex(g, "assets/door_c.xpm");
	g->tex[TEX_DOOR_O] = load_tex(g, "assets/door_o.xpm");
	g->tex[TEX_WINDOW] = load_tex(g, "assets/window.xpm");
	g->tex[TEX_BUSH] = load_tex(g, "assets/bush.xpm");
	g->tex[TEX_WALL_CLASS] = load_tex(g, "assets/wall_class.xpm");
	g->tex[TEX_BOARD_1] = load_tex(g, "assets/board_1.xpm");
	g->tex[TEX_BOARD_2] = load_tex(g, "assets/board_2.xpm");
	g->tex[TEX_BOARD_3] = load_tex(g, "assets/board_3.xpm");
	g->tex[TEX_WALL_OUTSIDE] = load_tex(g, "assets/wall_outside.xpm");
	g->tex[TEX_WINDOW_OUTSIDE] = load_tex(g, "assets/window.xpm");
	g->tex[TEX_DOOR_C_OUTSIDE] = load_tex(g, "assets/door_c.xpm");
	g->tex[TEX_DOOR_O_OUTSIDE] = load_tex(g, "assets/door_o.xpm");
	g->tex[TEX_FLOOR] = load_tex(g, "assets/floor.xpm");
	g->tex[TEX_GROUND] = load_tex(g, "assets/ground.xpm");
	g->tex[TEX_GRASS] = load_tex(g, "assets/grass.xpm");
	g->tex[TEX_CEILING] = load_tex(g, "assets/ceiling.xpm");
	g->tex[TEX_SPR_TREE_0] = load_tex(g, "assets/tree_0.xpm");
	g->tex[TEX_SPR_TREE_1] = load_tex(g, "assets/tree_1.xpm");
	g->tex[TEX_SPR_LADDER] = load_tex(g, "assets/ladder.xpm");
	g->tex[TEX_PORTAL_0_0] = load_tex(g, "assets/portal_0_0.xpm");
	g->tex[TEX_PORTAL_0_1] = load_tex(g, "assets/portal_0_1.xpm");
	g->tex[TEX_PORTAL_1_0] = load_tex(g, "assets/portal_1_0.xpm");
	g->tex[TEX_PORTAL_1_1] = load_tex(g, "assets/portal_1_1.xpm");
	load_assets_gui(g);
}
