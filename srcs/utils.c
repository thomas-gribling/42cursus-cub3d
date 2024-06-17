/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 08:41:10 by tgriblin          #+#    #+#             */
/*   Updated: 2024/06/17 15:22:11 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	tab_free(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

int	put_error(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		write(2, &s[i], 1);
	return (1);
}

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t			i;
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	i = 0;
	ptr1 = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (ptr1[i] && ptr2[i] && ptr1[i] == ptr2[i] && i < n - 1)
		i++;
	return (ptr1[i] - ptr2[i]);
}

int	color_atoi(char *line, int start)
{
	int	i;
	int	out;

	while (line[start] == ' ')
		start++;
	i = start;
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	if (i - start > 3 || i - start < 1)
		return (-1);
	if (line[i] && line[i] != ',' && line[i] != ' ')
		return (-1);
	out = 0;
	i = start - 1;
	while (line[++i] >= '0' && line[i] <= '9')
		out = out * 10 + line[i] - '0';
	if (out > 255)
		return (-1);
	return (out);
}

int	rgb_to_hex(int *rgb)
{
	(void)rgb;
	return (0x000000);
}
