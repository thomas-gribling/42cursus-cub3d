/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 12:16:40 by tgriblin          #+#    #+#             */
/*   Updated: 2024/09/12 09:34:54 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	get_texture(t_game *g, char c)
{
	(void)g;
	if (c == '2')
		return (TEX_WALL_SIGN);
	if (c == '3')
		return (TEX_DOOR_C);
	if (c == '4')
		return (TEX_WINDOW);
	if (c == '5')
		return (TEX_WALL_CLASS);
	if (c >= '6' && c <= '8')
		return (TEX_BOARD_1 + c - '0' - 6);
	if (c == '9')
		return (TEX_WALL_BRICKS);
	return (TEX_WALL);
}
