/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 10:07:31 by tgriblin          #+#    #+#             */
/*   Updated: 2024/09/10 16:43:47 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	is_in_str(char *s, char c)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] == c)
			return (1);
	return (0);
}

int	first_map_char(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] == ' ')
		i++;
	return (i);
}

unsigned int	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	int_len(long n)
{
	int	out;

	out = 1;
	if (n < 0)
	{
		n = -n;
		out += 1;
	}
	while (n > 9)
	{
		out++;
		n /= 10;
	}
	return (out);
}

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}
