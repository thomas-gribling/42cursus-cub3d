/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:30:05 by tgriblin          #+#    #+#             */
/*   Updated: 2024/09/23 09:17:51 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"
#include "../include/gnl.h"

int	parse_map_layout(t_map **map, char *path)
{
	char	*line;
	int		f;

	f = open(path, O_RDONLY);
	if (f < 0)
		return (put_error("Error: unable to open the map!\n"));
	*map = malloc(sizeof(t_map));
	(*map)->content = NULL;
	(*map)->height = 0;
	(*map)->width = 0;
	line = get_next_line(f);
	while (line)
	{
		if (ft_strlen(line) > (*map)->width)
			(*map)->width = ft_strlen(line);
		(*map)->content = tab_append((*map)->content, line, 1);
		(*map)->height++;
		line = get_next_line(f);
	}
	close(f);
	return (0);
}

void	read_spr(t_map **map)
{
	int	x;
	int	y;

	(*map)->spr_amt = 0;
	(*map)->spr = NULL;
	y = -1;
	while ((*map)->content[++y])
	{
		x = -1;
		while ((*map)->content[y][++x])
			if (is_sprite((*map)->content[y][x]))
				append_spr(map, x, y);
	}
}
