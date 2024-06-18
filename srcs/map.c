/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:30:05 by tgriblin          #+#    #+#             */
/*   Updated: 2024/06/18 09:43:02 by tgriblin         ###   ########.fr       */
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
	if (rgb[0] < 0 || rgb[1] < 0 || rgb[2] < 0)
		return (1);
	if (!ft_strncmp(line, "F ", 2))
		g->colors[0] = rgb_to_hex(rgb);
	if (!ft_strncmp(line, "C ", 2))
		g->colors[1] = rgb_to_hex(rgb);
	return (0);
}

static int	get_texture(t_game *g, char *line)
{
	int	i;
	int	j;
	int	tex;

	if (!ft_strncmp(line, "NO ", 3))
		tex = 0;
	if (!ft_strncmp(line, "SO ", 3))
		tex = 1;
	if (!ft_strncmp(line, "WE ", 3))
		tex = 2;
	if (!ft_strncmp(line, "EA ", 3))
		tex = 3;
	i = 2;
	while (line[i] && line[i] == ' ')
		i++;
	j = i;
	while (line[j])
		j++;
	g->tex_paths[tex] = malloc(j - i + 1);
	j = i;
	while (line[++j])
		g->tex_paths[tex][j - i] = line[j];
	g->tex_paths[tex][j - i] = '\0';
	return (0);
}

static int	parse_map(t_game *g, char *path)
{
	int		f;
	char	*line;
	int		error;

	error = 0;
	f = open(path, O_RDONLY);
	if (f < 0)
		return (put_error("Error: unable to open the map!\n"));
	line = get_next_line(f);
	while (line)
	{
		if (!error)
		{
			if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
				error += get_color(g, line);
			if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
				|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
					error += get_texture(g, line);
		}
		free(line);
		line = get_next_line(f);
	}
	return (error > 0);
}

int	load_map(t_game *g, char *path)
{
	g->colors[0] = 0;
	g->colors[1] = 0;
	g->tex_paths = malloc(4 * sizeof(char *));
	if (parse_map(g, path))
		return (put_error("Error while parsing the map!\n"));
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
