/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:30:05 by tgriblin          #+#    #+#             */
/*   Updated: 2024/06/17 15:27:13 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/gnl.h"

int	check_map_format(char *map)
{
	int	i;

	if (!map)
		return (1);
	i = 0;
	while (map[i])
		i++;
	if (i < 4)
		return (1);
	i--;
	if (map[i] == 'b')
		if (map[i - 1] == 'u')
			if (map[i - 2] == 'c')
				if (map[i - 3] == '.')
					return (0);
	return (1);
		
}

static int	get_color(t_game *g, char *line)
{
	int	i;
	int	rgb[3];

	i = 1;
	rgb[0] = color_atoi(line, 1);
	while (line[i] && line[i] != ',')
		i++;
	if (!line[i++])
		return (1);
	rgb[1] = color_atoi(line, i);
	while (line[i] && line[i] != ',')
		i++;
	if (!line[i++])
		return (1);
	rgb[2] = color_atoi(line, i);
	while (line[++i])
		if (line[i] != ' ' && (line[i] < '0' || line[i] > '9'))
			return (1);
	if (!ft_strncmp(line, "C ", 3))
		g->colors[0] = rgb_to_hex(rgb);
	if (!ft_strncmp(line, "F ", 3))
		g->colors[1] = rgb_to_hex(rgb);
	return (0);
}

static int	read_map(t_game *g, char *path)
{
	int		f;
	char	*line;

	f = open(path, O_RDONLY);
	if (f < 0)
		return (put_error("Error: unable to open the map!\n"));
	line = get_next_line(f);
	while (line)
	{
		if (!ft_strncmp(line, "C ", 3) || !ft_strncmp(line, "F ", 3))
			get_color(g, line);
		free(line);
		line = get_next_line(f);
	}
	return (0);
}

int	load_map(t_game *g, char *path)
{
	if (read_map(g, path))
		return (1);
	g->map = malloc(sizeof(t_map));
	g->map->content = malloc(11 * sizeof(char *));
	g->map->content[0] = "1111111111";
	g->map->content[1] = "1000000111";
	g->map->content[2] = "1010000011";
	g->map->content[3] = "1000000001";
	g->map->content[4] = "1000000001";
	g->map->content[5] = "1000000001";
	g->map->content[6] = "1000000001";
	g->map->content[7] = "1100000011";
	g->map->content[8] = "1110000111";
	g->map->content[9] = "1111111111";
	g->map->content[10] = NULL;
	g->map->width = 10;
	g->map->height = 10;
	return (0);
}
