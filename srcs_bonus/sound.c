/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 22:18:14 by bgnnrs            #+#    #+#             */
/*   Updated: 2024/10/07 15:45:51 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static unsigned long	hashstr(const char *str)
{
	unsigned long	hash;
	int				c;

	hash = 5381;
	c = *str++;
	while ((c))
	{
		hash = ((hash << 5) + hash) + c;
		c = *str++;
	}
	return (hash);
}

static char	*is_attenued(char *base, int attenued)
{
	if (attenued)
		base = "paplay --volume=30000 assets/audio/";
	else
		base = "paplay --volume=40000 assets/audio/";
	return (base);
}

/* Play the .ogg file in parameter (name without path or extention) */
void	playsound(char *file, int wait, int stop, int attenued)
{
	char	*base;
	char	tmp[256];
	int		result;

	base = NULL;
	base = is_attenued(base, attenued);
	memset(tmp, 0, 256);
	memcpy(tmp, base, strlen(base));
	if (stop)
	{
		result = system("pkill -f paplay");
		if (result != 0)
			perror("");
	}
	if (hashstr(file) == 2784)
		return ;
	memcpy(&tmp[strlen(base)], file, strlen(file));
	if (!wait)
		base = ".ogg &";
	else
		base = ".ogg";
	memcpy(&tmp[strlen(tmp)], base, strlen(base));
	result = system(tmp);
	if (result != 0)
		perror("");
}

/* Play the .ogg file every [duration] milliseconds */
void	playsoundloop(t_game *g, char *file, unsigned int duration)
{
	g->loop_time = duration;
	g->looped_snd = file;
	playsound(file, 0, 0, 0);
	g->loop_start = get_time();
}

/* Stops all playing sounds */
void	stopallsounds(t_game *g)
{
	int	result;

	result = system("pkill -f paplay");
	(void)result;
	g->loop_start = 0;
}
