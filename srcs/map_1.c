/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:30:05 by tgriblin          #+#    #+#             */
/*   Updated: 2024/10/10 10:46:35 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	read_layout(t_game *g, char *line, int f)
{
	g->map = NULL;
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

int	parse_map_layout(t_game *g, char *path)
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
			if (map[y][x] != '1' && map[y][x] != '0' && map[y][x] != 'N'
				&& map[y][x] != 'S' && map[y][x] != 'E' && map[y][x] != 'W'
				&& map[y][x] != ' ')
				return (put_error("Error: invalid characters in map!\n"));
			if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E'
				|| map[y][x] == 'W')
				if (!(x == 0 || y == 0 || !map[y + 1] || map[y][x + 1] == '\0'
					|| map[y][x + 1] == '\n' || map[y + 1][x] == ' '
					|| map[y - 1][x] == ' '  || map[y][x + 1] == ' '
					|| map[y][x - 1] == ' '))
				count++;
		}
	}
	if (count < 1)
		return (put_error("Error: no player spawn in map!\n"));
	if (count > 1)
		return (put_error("Error: too many player spawns in map!\n"));
	return (0);
}

static int	check_bounds_loop(char **map, char *state, int x, int y)
{
	if (map[y][x] == '0' && state[x] != '1')
		return (1);
	if (map[y][x] == '1' && state[x] != '1')
		state[x] = '1';
	if (map[y][x] == ' ' && (map[y + 1][x] == '0'
		|| map[y - 1][x] == '0' || (x > 0 && map[y][x - 1] == '0')
		|| (x < ft_strlen(map[y]) && map[y][x + 1] == '0')))
		return (1);
	if ((x == first_map_char(map[y]) && map[y][x] == '0')
		|| (x == ft_strlen(map[y]) - 1 && map[y][x] == '0'))
		return (1);
	return (0);
}

int	check_map_bounds(char **map, int y)
{
	int		x;
	char	*state;

	state = ft_strdup(map[0]);
	if (is_in_str(state, '0'))
		return (free(state), 1);
	while (map[++y + 1])
	{
		x = -1;
		while (map[y][++x])
			if (check_bounds_loop(map, state, x, y))
				return (free(state), 1);
	}
	free(state);
	state = ft_strdup(map[y]);
	if (is_in_str(state, '0'))
		return (free(state), 1);
	return (free(state), 0);
}
