/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 08:46:26 by tgriblin          #+#    #+#             */
/*   Updated: 2024/09/30 16:51:22 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

t_tex	load_tex(t_game *g, char *path)
{
	t_tex	s;

	s.ptr = mlx_xpm_file_to_image(g->mlx, path, &s.width, &s.height);
	s.addr = mlx_get_data_addr(s.ptr, &s.bpp, &s.line_len, &s.endian);
	return (s);
}

static void	load_assets_4(t_game *g)
{
	g->tex[TEX_NPC_STUDENT_B_0] = load_tex(g, "assets/npc/student_ub.xpm");
	g->tex[TEX_NPC_STUDENT_B_1] = load_tex(g, "assets/npc/student_db.xpm");
	g->tex[TEX_NPC_STUDENT_DEAD] = load_tex(g, "assets/npc/student_dead.xpm");
	g->tex[TEX_NPC_BULLY_F_0] = load_tex(g, "assets/npc/bully_uf.xpm");
	g->tex[TEX_NPC_BULLY_F_1] = load_tex(g, "assets/npc/bully_df.xpm");
	g->tex[TEX_NPC_BULLY_B_0] = load_tex(g, "assets/npc/bully_ub.xpm");
	g->tex[TEX_NPC_BULLY_B_1] = load_tex(g, "assets/npc/bully_db.xpm");
	g->tex[TEX_NPC_BULLY_DEAD] = load_tex(g, "assets/npc/bully_dead.xpm");
	g->tex[TEX_NPC_CHAD_H] = load_tex(g, "assets/npc/chad_h.xpm");
	g->tex[TEX_NPC_CHAD_I] = load_tex(g, "assets/npc/chad.xpm");
	g->tex[TEX_NPC_CHAD_A] = load_tex(g, "assets/npc/chad_a.xpm");
	g->tex[TEX_NPC_CHAD_D] = load_tex(g, "assets/npc/chad_d.xpm");
	g->tex[TEX_END_0_BG] = load_tex(g, "assets/ending_0.xpm");
	g->tex[TEX_END_1_BG] = load_tex(g, "assets/ending_1.xpm");
	g->tex[TEX_END_2_BG] = load_tex(g, "assets/ending_2.xpm");
	g->tex[TEX_END_3_BG] = load_tex(g, "assets/ending_3.xpm");
	g->tex[TEX_END_4_BG] = load_tex(g, "assets/ending_4.xpm");
}

static void	load_assets_3(t_game *g)
{
	g->tex[TEX_GUI_5] = load_tex(g, "assets/gui/5.xpm");
	g->tex[TEX_GUI_6] = load_tex(g, "assets/gui/6.xpm");
	g->tex[TEX_GUI_7] = load_tex(g, "assets/gui/7.xpm");
	g->tex[TEX_GUI_8] = load_tex(g, "assets/gui/8.xpm");
	g->tex[TEX_GUI_9] = load_tex(g, "assets/gui/9.xpm");
	g->tex[TEX_GUI_SEP] = load_tex(g, "assets/gui/sep.xpm");
	g->tex[TEX_GUI_MAPWALL] = load_tex(g, "assets/gui/minimap_wall.xpm");
	g->tex[TEX_GUI_MAPPLAYER] = load_tex(g, "assets/gui/minimap_player.xpm");
	g->tex[TEX_GUI_SPLASH_0] = load_tex(g, "assets/gui/splash_0.xpm");
	g->tex[TEX_GUI_SPLASH_1] = load_tex(g, "assets/gui/splash_1.xpm");
	g->tex[TEX_GUI_SPLASH_2] = load_tex(g, "assets/gui/splash_2.xpm");
	g->tex[TEX_GUI_SPLASH_3] = load_tex(g, "assets/gui/splash_3.xpm");
	g->tex[TEX_NPC_JERAU] = load_tex(g, "assets/npc/jerau.xpm");
	g->tex[TEX_NPC_PIRATE_0] = load_tex(g, "assets/npc/pirate_0.xpm");
	g->tex[TEX_NPC_PIRATE_1] = load_tex(g, "assets/npc/pirate_1.xpm");
	g->tex[TEX_NPC_PIRATE_2] = load_tex(g, "assets/npc/pirate_2.xpm");
	g->tex[TEX_NPC_PIRATE_3] = load_tex(g, "assets/npc/pirate_3.xpm");
	g->tex[TEX_NPC_PIRATE_4] = load_tex(g, "assets/npc/pirate_4.xpm");
	g->tex[TEX_NPC_PIRATE_5] = load_tex(g, "assets/npc/pirate_5.xpm");
	g->tex[TEX_NPC_PIRATE_6] = load_tex(g, "assets/npc/pirate_6.xpm");
	g->tex[TEX_NPC_PIRATE_7] = load_tex(g, "assets/npc/pirate_7.xpm");
	g->tex[TEX_NPC_POULET] = load_tex(g, "assets/npc/poulet.xpm");
	g->tex[TEX_NPC_STUDENT_F_0] = load_tex(g, "assets/npc/student_uf.xpm");
	g->tex[TEX_NPC_STUDENT_F_1] = load_tex(g, "assets/npc/student_df.xpm");
	load_assets_4(g);
}

static void	load_assets_2(t_game *g)
{
	g->tex[TEX_GROUND] = load_tex(g, "assets/ground.xpm");
	g->tex[TEX_GROUND_BACKROOMS] = load_tex(g, "assets/ground_backrooms.xpm");
	g->tex[TEX_GRASS] = load_tex(g, "assets/grass.xpm");
	g->tex[TEX_CARPET] = load_tex(g, "assets/carpet.xpm");
	g->tex[TEX_CEILING] = load_tex(g, "assets/ceiling.xpm");
	g->tex[TEX_CEILING_TRAPDOOR] = load_tex(g, "assets/ceiling_trapdoor.xpm");
	g->tex[TEX_SPR_TREE_0] = load_tex(g, "assets/tree_0.xpm");
	g->tex[TEX_SPR_TREE_1] = load_tex(g, "assets/tree_1.xpm");
	g->tex[TEX_PORTAL_0] = load_tex(g, "assets/portal_0.xpm");
	g->tex[TEX_PORTAL_1] = load_tex(g, "assets/portal_1.xpm");
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
	load_assets_3(g);
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
	g->tex[TEX_BUSH_BACKROOMS] = load_tex(g, "assets/bush_backrooms.xpm");
	g->tex[TEX_WALL_CLASS] = load_tex(g, "assets/wall_class.xpm");
	g->tex[TEX_BOARD_1] = load_tex(g, "assets/board_1.xpm");
	g->tex[TEX_BOARD_2] = load_tex(g, "assets/board_2.xpm");
	g->tex[TEX_BOARD_3] = load_tex(g, "assets/board_3.xpm");
	g->tex[TEX_WALL_OUTSIDE] = load_tex(g, "assets/wall_outside.xpm");
	g->tex[TEX_WINDOW_OUTSIDE] = load_tex(g, "assets/win.xpm");
	g->tex[TEX_DOOR_C_OUTSIDE] = load_tex(g, "assets/o_doorc.xpm");
	g->tex[TEX_DOOR_O_OUTSIDE] = load_tex(g, "assets/o_dooro.xpm");
	g->tex[TEX_WALL_BSMT] = load_tex(g, "assets/lvl2/wall.xpm");
	g->tex[TEX_WALL_SIGN_BSMT] = load_tex(g, "assets/lvl2/wall_sign.xpm");
	g->tex[TEX_WINDOW_BSMT] = load_tex(g, "assets/lvl2/window.xpm");
	g->tex[TEX_DOOR_C_BSMT] = load_tex(g, "assets/lvl2/doorc.xpm");
	g->tex[TEX_DOOR_O_BSMT] = load_tex(g, "assets/lvl2/dooro.xpm");
	g->tex[TEX_WALL_BACKROOMS_0] = load_tex(g, "assets/backrooms_0.xpm");
	g->tex[TEX_WALL_BACKROOMS_1] = load_tex(g, "assets/backrooms_1.xpm");
	g->tex[TEX_WALL_BACKROOMS_2] = load_tex(g, "assets/backrooms_2.xpm");
	g->tex[TEX_WALL_BACKROOMS_3] = load_tex(g, "assets/backrooms_3.xpm");
	g->tex[TEX_WALL_BACKROOMS_4] = load_tex(g, "assets/backrooms_4.xpm");
	g->tex[TEX_FLOOR] = load_tex(g, "assets/floor.xpm");
	g->tex[TEX_FLOOR_TRAPDOOR] = load_tex(g, "assets/floor_trapdoor.xpm");
	load_assets_2(g);
}
