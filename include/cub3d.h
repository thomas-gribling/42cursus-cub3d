/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 08:10:05 by tgriblin          #+#    #+#             */
/*   Updated: 2024/06/11 08:52:28 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

# define GAME_TITLE "Shoot the bullies"
# define WIDTH 1200
# define HEIGHT 900

# define KEY_ESCAPE 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

# ifndef BONUS_MODE
#  define BONUS_MODE 0
# endif // BONUS_MODE

# define TEX_AMT 3
# define TEX_WALL 0
# define TEX_FLOOR 1
# define TEX_CEIL 2

typedef struct s_map
{
	char	**content;
	int		width;
	int		height;
}			t_map;

typedef struct s_cam
{
	double		dist[25];
	double		cam_x;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		ray_dir_x;
	double		ray_dir_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	int			step_x;
	int			step_y;
	int			map_x;
	int			map_y;
	int			hit;
	int			side;
	double		perp_wall_dist;
	int			line_h;
	int			bounds[2];
	double		speed_m;
	double		speed_r;
}				t_cam;

typedef struct s_tex
{
	void	*ptr;
	int		width;
	int		height;
}			t_tex;

typedef struct s_player
{
	double	x;
	double	y;
	t_cam	*cam;
}			t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	int			time[2];
	t_map		*map;
	t_player	*p;
	t_tex	*tex;
}				t_game;

void	load_assets(t_game *g);
int		raycast(t_game *g, t_cam *c);
void	move_player(t_game *g, t_cam *c, int keycode);
void	rotate_player(t_cam *c, int keycode);

void	tab_free(char **tab);
int		ft_max(int a, int b);

#endif // CUB3D_H