/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:51:59 by tgriblin          #+#    #+#             */
/*   Updated: 2024/10/10 11:01:02 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
