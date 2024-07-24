/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 12:16:40 by tgriblin          #+#    #+#             */
/*   Updated: 2024/07/24 14:01:58 by tgriblin         ###   ########.fr       */
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
		return (TEX_DOOR_O);
	return (TEX_WALL);
}
