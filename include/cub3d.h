/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 08:10:05 by tgriblin          #+#    #+#             */
/*   Updated: 2024/06/28 10:46:48 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>

# define GAME_TITLE "KTB! - KILL THE BULLIES!"
# define WIDTH 1200
# define HEIGHT 900

# define KEY_ESCAPE 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

# define TEX_AMT 4
# define TEX_WALL_N 0
# define TEX_WALL_E 1
# define TEX_WALL_S 2
# define TEX_WALL_W 3

typedef struct s_map
{
	char	**content;
	int		width;
	int		height;
}			t_map;

typedef struct s_tex
{
	void	*ptr;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}			t_tex;

typedef struct s_cam
{
	double			cam_x;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			ray_dir_x;
	double			ray_dir_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_x;
	double			delta_y;
	int				step_x;
	int				step_y;
	int				map_x;
	int				map_y;
	int				hit;
	int				side;
	double			perp_wall_dist;
	int				line_h;
	int				bounds[2];
	double			speed_m;
	double			speed_r;
	double			wall_x;
	int				tex_x;
	int				tex_y;
	double			step;
	double			tex_pos;
	unsigned int	color;
	t_tex			buff;
}					t_cam;

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
	t_tex		*tex;
	int			colors[2];
	char		**tex_paths;
}				t_game;

int				check_map_format(char *map);
int				parse_map_infos(t_game *g, char *path);
int				parse_map_layout(t_game *g, char *path);
int				check_map_bounds(char **map, int y);
int				check_map_chars(char **map);

void			init_values(t_game *g);

void			load_assets(t_game *g);
t_tex			load_tex(t_game *g, char *path, int width, int height);
void			tex_pixel_put(t_tex *tex, int x, int y, int color);
unsigned int	tex_get_pixel(t_tex *tex, int x, int y);
void			reset_buffer(t_game *g, t_tex *buff);

int				raycast(t_game *g, t_cam *c);
int				get_wall_tex(t_cam *c);
void			move_player(t_game *g, t_cam *c, int keycode);
void			rotate_player(t_cam *c, int keycode);

int				put_error(char *s);
int				ft_strncmp(char *s1, char *s2, size_t n);
int				color_atoi(char *line, int start);
int				rgb_to_hex(int *rgb);
char			*ft_strdup(char *s);
void			tab_free(char **tab);
char			**tab_append(char **old, char *s, int do_free);
char			*ft_strdup_endl(char *s);
int				is_in_str(char *s, char c);
int				first_map_char(char *s);

#endif // CUB3D_H
