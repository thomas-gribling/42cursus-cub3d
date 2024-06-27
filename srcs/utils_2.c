/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 08:41:49 by tgriblin          #+#    #+#             */
/*   Updated: 2024/06/27 08:54:33 by tgriblin         ###   ########.fr       */
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
			new[i] = ft_strdup(old[i]);
	}
	new[i++] = ft_strdup(s);
	new[i] = NULL;
	tab_free(old);
	if (do_free)
		free(s);
	return (new);
}
