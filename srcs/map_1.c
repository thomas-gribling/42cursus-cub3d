/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:30:05 by tgriblin          #+#    #+#             */
/*   Updated: 2024/06/28 09:52:33 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/gnl.h"

static int	read_layout(t_game *g, char *line, int f)
{
	if (!line)
		return (put_error("Error: missing map in file.\n"));
	g->map = malloc(sizeof(t_map));
	g->map->height = 0;
	g->map->width = 0;
	g->map->content = NULL;
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

static int	parse_map_layout(t_game *g, char *path)
{
	char	*line;
	int		f;
	int		elements;

	f = open(path, O_RDONLY);
	if (f < 0)
		return (put_error("Error: unable to open the map!\n"));
	elements = 0;
	line = get_next_line(f);
	while (line && elements != 6)
	{
		if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2)
			|| !ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
			|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
			elements++;
		free(line);
		line = get_next_line(f);
	}
	while (line && !ft_strncmp(line, "\n", 1))
	{
		free(line);
		line = get_next_line(f);
	}
	return (read_layout(g, line, f));
}

static int	check_map_chars(char **map)
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
			if (map[y][x] != '1' && map[y][x] != '0' && map[y][x] != 'N'
				&& map[y][x] != 'S' && map[y][x] != 'E' && map[y][x] != 'W'
				&& map[y][x] != ' ')
				return (put_error("Error: invalid characters in map!\n"));
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

static int	check_map_bounds(char **map)
{
	(void)map;
	return (0);
}

int	load_map(t_game *g, char *path)
{
	g->colors[0] = 0;
	g->colors[1] = 0;
	g->tex_paths = malloc(5 * sizeof(char *));
	g->tex_paths[4] = NULL;
	if (parse_map_infos(g, path))
		return (put_error("Error while parsing the map!\n"));
	if (parse_map_layout(g, path))
		return (put_error("Error while parsing the map!\n"));
	if (check_map_bounds(g->map->content))
		return (put_error("Error: map bounds must be walls!\n"));
	return (check_map_chars(g->map->content));
}
