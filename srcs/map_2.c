/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:49:10 by tgriblin          #+#    #+#             */
/*   Updated: 2024/10/10 10:57:09 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
		g->colors[1] = rgb_to_hex(rgb);
	if (!ft_strncmp(line, "C ", 2))
		g->colors[0] = rgb_to_hex(rgb);
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
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	j = i;
	while (line[j] && line[j] != '\n')
		j++;
	free(g->tex_paths[tex]);
	g->tex_paths[tex] = malloc(j - i + 1);
	j = i - 1;
	while (line[++j] && line[j] != '\n')
		g->tex_paths[tex][j - i] = line[j];
	g->tex_paths[tex][j - i] = '\0';
	return (0);
}

static void	check_dirs_vals(t_game *g, char *line, int *error)
{
	if (!ft_strncmp(line, "NO ", 3) && !g->dir_found[0])
		g->dir_found[0] = 1;
	else if (!ft_strncmp(line, "SO ", 3) && !g->dir_found[1])
		g->dir_found[1] = 1;
	else if (!ft_strncmp(line, "WE ", 3) && !g->dir_found[2])
		g->dir_found[2] = 1;
	else if (!ft_strncmp(line, "EA ", 3) && !g->dir_found[3])
		g->dir_found[3] = 1;
	else
		(*error)++;
}

static void	parse_infos_loop(t_game *g, char *line, int *error, int *elements)
{
	if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
	{
		if (!ft_strncmp(line, "F ", 2) && !g->f_found)
			g->f_found = 1;
		else if (!ft_strncmp(line, "C ", 2) && !g->c_found)
			g->c_found = 1;
		else
			(*error)++;
		*error += get_color(g, line);
		(*elements)++;
	}
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
	{
		check_dirs_vals(g, line, error);
		*error += get_texture(g, line);
		(*elements)++;
	}
}

int	parse_map_infos(t_game *g, char *path, int error)
{
	int		f;
	char	*line;
	int		elements;
	int		i;

	elements = 0;
	f = open(path, O_RDONLY);
	if (f < 0)
		return (1);
	g->tex_paths = malloc(5 * sizeof(char *));
	i = -1;
	while (g->tex_paths && ++i < 4)
		g->tex_paths[i] = malloc(sizeof(char));
	g->tex_paths[4] = NULL;
	line = get_next_line(f);
	while (line)
	{
		if (!error)
			parse_infos_loop(g, line, &error, &elements);
		free(line);
		line = get_next_line(f);
	}
	close(f);
	return (error > 0 || elements < 6);
}
