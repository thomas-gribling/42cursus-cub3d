/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 08:10:05 by tgriblin          #+#    #+#             */
/*   Updated: 2024/09/10 13:25:21 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <sys/time.h>

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
# define KEY_1 49
# define KEY_2 50

# define LEFT_CLICK 1
# define RIGHT_CLICK 3
# define WHEEL_UP 4
# define WHEEL_DOWN 5

# define TEX_AMT 30
# define TEX_MENU_BG 0
# define TEX_WALL 1
# define TEX_WALL_SIGN 2
# define TEX_DOOR_C 3
# define TEX_DOOR_O 4
# define TEX_WINDOW 5
# define TEX_WALL_CLASS 6
# define TEX_BOARD_1 7
# define TEX_BOARD_2 8
# define TEX_BOARD_3 9
# define TEX_FLOOR 10
# define TEX_CEILING 11
# define TEX_GUI_INV_00_0 12
# define TEX_GUI_INV_00_1 13
# define TEX_GUI_INV_10_0 14
# define TEX_GUI_INV_10_1 15
# define TEX_GUI_INV_01_0 16
# define TEX_GUI_INV_01_1 17
# define TEX_GUI_INV_11_0 18
# define TEX_GUI_INV_11_1 19
# define TEX_GUI_0 20
# define TEX_GUI_1 21
# define TEX_GUI_2 22
# define TEX_GUI_3 23
# define TEX_GUI_4 24
# define TEX_GUI_5 25
# define TEX_GUI_6 26
# define TEX_GUI_7 27
# define TEX_GUI_8 28
# define TEX_GUI_9 29

typedef struct s_map
{
	char	**content;
	int		*sizes;
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
	double			ray_dir_x_0;
	double			ray_dir_x_1;
	double			ray_dir_y_0;
	double			ray_dir_y_1;
	int				p;
	double			pos_z;
	double			row_distance;
	double			floor_step_x;
	double			floor_step_y;
	double			floor_x;
	double			floor_y;
	int				cell_x;
	int				cell_y;
	int				tx[2];
	int				ty[2];
}					t_cam;

typedef struct s_player
{
	double	x;
	double	y;
	t_cam	*cam;
}			t_player;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	t_map			*map;
	t_player		*p;
	t_tex			*tex;
	t_tex			tmp_tex;
	int				scene;
	int				curr_slot;
	int				slots[2];
	unsigned int	last_wheel;
	unsigned int	start;
}				t_game;

int				parse_map_layout(t_game *g, char *path);
int				check_map_bounds(char **map, int y);
int				check_map_chars(char **map);

void			init_values(t_game *g);

void			load_assets(t_game *g);
t_tex			load_tex(t_game *g, char *path, int width, int height);
void			tex_put(t_tex *to, t_tex *from, int x, int y);
void			tex_put_scale(t_tex *to, t_tex *from, int x, int y);
void			tex_pixel_put(t_tex *tex, int x, int y, int color);
unsigned int	tex_get_pixel(t_tex *tex, int x, int y);
void			reset_buffer(t_tex *buff);

void			update_screen(t_game *g);
void			raycast(t_game *g, t_cam *c, int x);
void			raycast_floor_ceiling(t_game *g, t_cam *c);
int				get_texture(t_game *g, char c);
void			move_player(t_game *g, t_cam *c, int keycode);
void			rotate_player(t_cam *c, int keycode);
void			switch_slots(t_game *g, int keycode);

int				put_error(char *s);
int				ft_strncmp(char *s1, char *s2, size_t n);
int				color_atoi(char *line, int start);
int				rgb_to_hex(int *rgb);
char			*ft_strdup(char *s);
void			tab_free(char **tab);
char			**tab_append(char **old, char *s, int do_free);
char			*ft_strdup_endl(char *s);
int				is_prohibited_char(char c);
int				is_in_str(char *s, char c);
int				first_map_char(char *s);
int				int_len(long n);
unsigned int	get_time(void);

#endif // CUB3D_BONUS_H
