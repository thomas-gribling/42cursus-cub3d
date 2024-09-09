/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:44:51 by tgriblin          #+#    #+#             */
/*   Updated: 2024/09/09 08:47:20 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"
#include "../mlx/mlx.h"

void	draw_gui(t_game *g, t_cam *c)
{
	if (!g->slots[0] && !g->slots[1])
		tex_tex_put(&c->buff, &g->tex[TEX_GUI_INV_00_0 + g->curr_slot], 0, 0);
	if (g->slots[0] && !g->slots[1])
		tex_tex_put(&c->buff, &g->tex[TEX_GUI_INV_10_0 + g->curr_slot], 0, 0);
	if (!g->slots[0] && g->slots[1])
		tex_tex_put(&c->buff, &g->tex[TEX_GUI_INV_01_0 + g->curr_slot], 0, 0);
	if (g->slots[0] && g->slots[1])
		tex_tex_put(&c->buff, &g->tex[TEX_GUI_INV_11_0 + g->curr_slot], 0, 0);
}
