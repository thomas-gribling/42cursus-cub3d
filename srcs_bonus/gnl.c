/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 08:56:36 by tgriblin          #+#    #+#             */
/*   Updated: 2024/09/25 18:30:39 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

char	*ft_fill_stash(int fd, char *stash)
{
	char	*out;
	char	*tmp;
	int		rd;

	tmp = malloc(1001);
	if (stash)
	{
		out = ft_strdup(stash);
		free(stash);
	}
	else
		out = ft_strdup("");
	if (!tmp || !out)
		return (free_null(tmp, out));
	rd = 1;
	while (!ft_strchr(out, '\n') && rd > 0)
	{
		rd = read(fd, tmp, 1000);
		if (rd < 0)
			return (free_null(tmp, out));
		tmp[rd] = '\0';
		out = ft_strjoin(out, tmp);
	}
	free(tmp);
	return (out);
}

char	*ft_get_line(char *stash)
{
	char	*out;
	int		i;

	i = 0;
	if (!stash || !(*stash))
		return (NULL);
	while (stash[i] != '\n' && stash[i])
		i++;
	out = malloc(i + 2);
	if (!out)
		return (NULL);
	i = 0;
	while (stash[i] != '\n' && stash[i])
	{
		out[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
	{
		out[i] = '\n';
		i++;
	}
	out[i] = '\0';
	return (out);
}

char	*ft_del_line(char *stash)
{
	char	*out;
	int		i;
	int		j;

	i = 0;
	while (stash[i] != '\n' && stash[i])
		i++;
	i++;
	out = malloc(ft_strlen(stash) - i + 2);
	if (!out)
		return (NULL);
	j = 0;
	while (stash[i + j - 1])
	{
		out[j] = stash[i + j];
		j++;
	}
	out[j] = '\0';
	free(stash);
	return (out);
}

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*line;

	if (fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	stash = ft_fill_stash(fd, stash);
	if (!stash || !(*stash))
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	line = ft_get_line(stash);
	stash = ft_del_line(stash);
	return (line);
}
