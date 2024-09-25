/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:30:05 by tgriblin          #+#    #+#             */
/*   Updated: 2024/09/25 18:24:10 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static void	append_spr(t_map **map, int x, int y)
{
	t_sprite	*new;
	int			i;

	i = 0;
	new = malloc(((*map)->spr_amt + 1) * sizeof(t_sprite));
	if ((*map)->spr)
	{
		i = -1;
		while (++i < (*map)->spr_amt)
		{
			new[i].x = (*map)->spr[i].x;
			new[i].y = (*map)->spr[i].y;
			new[i].dist = (*map)->spr[i].dist;
			new[i].tex_id = (*map)->spr[i].tex_id;
		}
	}
	new[i].x = x + 0.5;
	new[i].y = y + 0.5;
	new[i].dist = 0.0;
	new[i].tex_id = 0;
	(*map)->spr_amt++;
	free((*map)->spr);
	(*map)->spr = new;
}

static void	read_spr(t_map **map)
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

static int	parse_map_layout(t_map **map, char *path)
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

t_map	*load_map(char *path)
{
	int		i;
	t_map	*map;

	map = NULL;
	if (parse_map_layout(&map, path))
	{
		if (map)
			tab_free(map->content);
		free(map);
		return (put_error("Error while parsing the map!\n"), NULL);
	}
	map->sizes = malloc(map->height * sizeof(int));
	i = -1;
	while (map->content[++i])
		map->sizes[i] = ft_strlen(map->content[i]);
	read_spr(&map);
	return (map);
}
