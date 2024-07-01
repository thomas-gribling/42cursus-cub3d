/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 08:41:49 by tgriblin          #+#    #+#             */
/*   Updated: 2024/06/28 09:58:54 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	tab_free(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

int	tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char	**tab_append(char **old, char *s, int do_free)
{
	char	**new;
	int		i;

	i = 0;
	if (!old)
		new = malloc(2 * sizeof(char *));
	else
	{
		new = malloc((tab_len(old) + 2) * sizeof(char *));
		i = -1;
		while (old[++i])
			new[i] = ft_strdup_endl(old[i]);
	}
	new[i++] = ft_strdup_endl(s);
	new[i] = NULL;
	tab_free(old);
	if (do_free)
		free(s);
	return (new);
}

char	*ft_strdup_endl(char *s)
{
	int		i;
	char	*dest;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	dest = malloc(i + 1);
	if (dest == NULL)
		return (NULL);
	i = -1;
	while (s[++i] && s[i] != '\n')
		dest[i] = s[i];
	dest[i] = '\0';
	return (dest);
}

int	get_wall_tex(t_cam *c)
{
	int	tex;

	if (c->side == 0 && c->ray_dir_x >= 0)
		tex = TEX_WALL_W;
	if (c->side == 0 && c->ray_dir_x < 0)
		tex = TEX_WALL_E;
	if (c->side == 1 && c->ray_dir_y >= 0)
		tex = TEX_WALL_N;
	if (c->side == 1 && c->ray_dir_y < 0)
		tex = TEX_WALL_S;
	return (tex);
}
