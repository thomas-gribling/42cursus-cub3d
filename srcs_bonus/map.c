/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:30:05 by tgriblin          #+#    #+#             */
/*   Updated: 2024/09/23 08:26:42 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"
#include "../include/gnl.h"

int	parse_map_layout(t_game *g, char *path)
{
	char	*line;
	int		f;

	f = open(path, O_RDONLY);
	if (f < 0)
		return (put_error("Error: unable to open the map!\n"));
	g->map = malloc(sizeof(t_map));
	g->map->height = 0;
	g->map->width = 0;
	g->map->content = NULL;
	line = get_next_line(f);
	while (line)
	{
		if (ft_strlen(line) > g->map->width)
			g->map->width = ft_strlen(line);
		g->map->content = tab_append(g->map->content, line, 1);
		g->map->height++;
		line = get_next_line(f);
	}
	close(f);
	return (0);
}

int	check_map_chars(char **map)
{
	int		x;
	int		y;
	int		count;

	count = 0;
	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E'
				|| map[y][x] == 'W')
				count++;
		}
	}
	if (count < 1)
		return (put_error("Error: no player spawn in map!\n"));
	if (count > 1)
		return (put_error("Error: too many player spawns in map!\n"));
	return (0);
}

void	read_spr(t_game *g, t_map *map)
{
	int	x;
	int	y;

	map->spr_amt = 0;
	map->spr = NULL;
	y = -1;
	while (map->content[++y])
	{
		x = -1;
		while (map->content[y][++x])
			if (is_sprite(map->content[y][x]))
				append_spr(g, map, x, y);
	}
}
