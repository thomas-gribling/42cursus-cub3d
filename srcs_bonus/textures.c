/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:03:06 by tgriblin          #+#    #+#             */
/*   Updated: 2024/09/26 09:52:34 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	tex_put(t_tex *to, t_tex *from, int x, int y)
{
	int	from_x;
	int	from_y;
	int	save_y;

	x -= 1;
	from_x = -1;
	save_y = y - 1;
	while (++from_x < from->width)
	{
		x++;
		y = save_y;
		from_y = -1;
		while (++from_y < from->height)
		{
			y++;
			tex_pixel_put(to, x, y, tex_get_pixel(from, from_x, from_y));
		}
	}
}

void	tex_put_scale(t_tex *to, t_tex *from, int x, int y)
{
	int		y_save;
	int		from_x;
	int		from_y;
	double	coeff[2];

	x -= 1;
	y_save = y - 1;
	from_x = -1;
	from_y = -1;
	coeff[0] = (double)from->width / (double)to->width;
	coeff[1] = (double)from->height / (double)to->height;
	while (++x < to->width)
	{
		from_x++;
		from_y = -1;
		y = y_save;
		while (++y < to->height)
		{
			from_y++;
			tex_pixel_put(to, x, y,
				tex_get_pixel(from, from_x * coeff[0], from_y * coeff[1]));
		}
	}
}

void	tex_pixel_put(t_tex *tex, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || x >= tex->width || y < 0 || y > tex->height)
		return ;
	pixel = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	if (color != 0xFF00FF)
		*(int *)pixel = color;
}

unsigned int	tex_get_pixel(t_tex *tex, int x, int y)
{
	char	*pixel;

	if (x < 0 || x >= tex->width || y < 0 || y > tex->height)
		return (0xFF00FF);
	pixel = tex->addr + (y * tex->line_len) + (x * tex->bpp / 8);
	return (*(unsigned int *)pixel);
}

void	reset_buffer(t_tex *buff)
{
	int	x;
	int	y;

	x = -1;
	while (++x < WIDTH)
	{
		y = -1;
		while (++y < HEIGHT)
		{
			if (y < HEIGHT / 2 && tex_get_pixel(buff, x, y) != 0x6AC9FB)
				tex_pixel_put(buff, x, y, 0x6AC9FB);
			if (y >= HEIGHT / 2 && tex_get_pixel(buff, x, y) != 0x00DD00)
				tex_pixel_put(buff, x, y, 0x00DD00);
		}
	}
}
