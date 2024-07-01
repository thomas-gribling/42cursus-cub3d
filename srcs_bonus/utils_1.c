/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 08:41:10 by tgriblin          #+#    #+#             */
/*   Updated: 2024/07/01 11:53:32 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

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
	if (line[i] && line[i] != ',' && line[i] != ' ' && line[i] != '\n')
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
	return (rgb[2] + rgb[1] * 16 * 16 + rgb[0] * 16 * 16 * 16 * 16);
}

char	*ft_strdup(char *s)
{
	int		i;
	char	*dest;

	i = 0;
	while (s[i])
		i++;
	dest = malloc(i + 1);
	if (dest == NULL)
		return (NULL);
	i = -1;
	while (s[++i])
		dest[i] = s[i];
	dest[i] = '\0';
	return (dest);
}
