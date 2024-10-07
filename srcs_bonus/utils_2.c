/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 08:41:49 by tgriblin          #+#    #+#             */
/*   Updated: 2024/10/07 09:36:51 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

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

t_tex	load_tex(t_game *g, char *path)
{
	t_tex	s;

	s.ptr = mlx_xpm_file_to_image(g->mlx, path, &s.width, &s.height);
	s.addr = mlx_get_data_addr(s.ptr, &s.bpp, &s.line_len, &s.endian);
	return (s);
}
