/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 08:10:05 by tgriblin          #+#    #+#             */
/*   Updated: 2024/09/24 17:21:01 by tgriblin         ###   ########.fr       */
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

# define COPS_TIMER 420

# define KEY_ESCAPE 65307
# define KEY_TAB 65289
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

# define TEX_AMT 61
# define TEX_MENU_BG 0
# define TEX_WALL 1
# define TEX_WALL_SIGN 2
# define TEX_WALL_CLASS 3
# define TEX_DOOR_C 4
# define TEX_DOOR_O 5
# define TEX_WINDOW 6
# define TEX_BOARD_1 7
# define TEX_BOARD_2 8
# define TEX_BOARD_3 9
# define TEX_BUSH 10
# define TEX_WALL_OUTSIDE 11
# define TEX_WINDOW_OUTSIDE 12
# define TEX_DOOR_C_OUTSIDE 13
# define TEX_DOOR_O_OUTSIDE 14
# define TEX_WALL_BACKROOMS_0 55
# define TEX_WALL_BACKROOMS_1 56
# define TEX_WALL_BACKROOMS_2 57
# define TEX_WALL_BACKROOMS_3 58
# define TEX_WALL_BACKROOMS_4 59
# define TEX_FLOOR 15
# define TEX_GROUND 16
# define TEX_GRASS 17
# define TEX_CARPET 60
# define TEX_CEILING 18
# define TEX_SPR_TREE_0 19
# define TEX_SPR_TREE_1 20
# define TEX_SPR_LADDER 21
# define TEX_GUI_INV_00_0 22
# define TEX_GUI_INV_00_1 23
# define TEX_GUI_INV_10_0 24
# define TEX_GUI_INV_10_1 25
# define TEX_GUI_INV_01_0 26
# define TEX_GUI_INV_01_1 27
# define TEX_GUI_INV_11_0 28
# define TEX_GUI_INV_11_1 29
# define TEX_GUI_0 30
# define TEX_GUI_1 31
# define TEX_GUI_2 32
# define TEX_GUI_3 33
# define TEX_GUI_4 34
# define TEX_GUI_5 35
# define TEX_GUI_6 36
# define TEX_GUI_7 37
# define TEX_GUI_8 38
# define TEX_GUI_9 39
# define TEX_GUI_SEP 40
# define TEX_GUI_MAPWALL 41
# define TEX_GUI_MAPPLAYER 42
# define TEX_GUI_SPLASH_0 43
# define TEX_GUI_SPLASH_1 44
# define TEX_GUI_SPLASH_2 45
# define TEX_GUI_SPLASH_3 46
# define TEX_PORTAL_0_0 47
# define TEX_PORTAL_0_1 48
# define TEX_PORTAL_1_0 49
# define TEX_PORTAL_1_1 50
# define TEX_NPC_CHAD_H 51
# define TEX_NPC_CHAD_I 52
# define TEX_NPC_CHAD_A 53
# define TEX_NPC_CHAD_D 54

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

typedef struct s_sprite
{
	double	x;
	double	y;
	double	dist;
	int		tex_id;
}				t_sprite;

typedef struct s_enemy
{
	double	x;
	double	y;
	int		type;
	int		is_dead;
}				t_enemy;

# define STUDENT 0
# define BULLY 1
# define BOSS 2
# define NEXTBOT_1 3
# define NEXTBOT_2 4
# define NEXTBOT_3 5

typedef struct s_map
{
	char		**content;
	int			*sizes;
	int			width;
	int			height;
	t_sprite	*spr;
	int			spr_amt;
}			t_map;

typedef struct s_coll
{
	int		map_x;
	int		map_y;
	int		map_x_visible;
	int		map_y_visible;
	int		side;
	int		tex_id;
	t_tex	tex;
}			t_coll;

typedef struct s_cam
{
	double			cam_x;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			ray_dir_x;
	double			ray_dir_y;
	double			ray_dir_x_visible;
	double			ray_dir_y_visible;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_x;
	double			delta_y;
	int				step_x;
	int				step_y;
	int				step_x_visible;
	int				step_y_visible;
	int				map_x;
	int				map_y;
	int				map_x_visible;
	int				map_y_visible;
	int				hit;
	int				side;
	t_coll			*colls;
	int				colls_amt;
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
	double			z_buffer[WIDTH];
	double			spr_x;
	double			spr_y;
	double			i_det;
	double			transf_x;
	double			transf_y;
	int				spr_screen_x;
	int				spr_h;
	int				draw_y[2];
	int				spr_w;
	int				draw_x[2];
	int				pix_x;
	int				pix_y;
	int				d;
}					t_cam;

typedef struct s_player
{
	double	x;
	double	y;
	int		moving_x;
	int		moving_y;
	int		rotating;
	t_cam	*cam;
}			t_player;

typedef struct s_portal
{
	int	map_x;
	int	map_y;
	int	face;
	int	is_placed;
}			t_portal;

# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3

typedef struct s_game
{
	void			*mlx;
	void			*win;
	t_map			*map;
	t_map			*maps[5];
	t_player		*p;
	t_tex			*tex;
	t_tex			tmp_tex;
	int				scene;
	int				curr_slot;
	int				slots[2];
	unsigned int	last_wheel;
	unsigned int	start;
	int				show_map;
	unsigned int	last_frame;
	unsigned int	last_fps_update;
	double			fps;
	int				mouse_middle_x;
	int				curr_level;
	t_portal		portals[2];
	unsigned int	splash_timer;
}				t_game;

t_map			*load_map(char *path);

void			init_values(t_game *g);

void			load_assets(t_game *g);
t_tex			load_tex(t_game *g, char *path);
void			tex_put(t_tex *to, t_tex *from, int x, int y);
void			tex_put_scale(t_tex *to, t_tex *from, int x, int y);
void			tex_pixel_put(t_tex *tex, int x, int y, int color);
unsigned int	tex_get_pixel(t_tex *tex, int x, int y);
void			reset_buffer(t_tex *buff);

int				close_game(t_game *g);
int				key_pressed(int keycode, t_game *g);
int				key_released(int keycode, t_game *g);
int				mouse_click(int button, int x, int y, t_game *g);
int				mouse_move(int x, int y, t_game *g);

void			update_screen(t_game *g);
void			raycast(t_game *g, t_cam *c, int x);
void			raycast_floor_ceiling(t_game *g, t_cam *c);
void			raycast_sprites(t_game *g, t_cam *c);
int				is_it_portal(t_game *g, int x, int y);
void			change_raycast_dir(t_game *g, t_cam *c);
int				get_texture(t_game *g, int x, int y);
double			dist_to_tile(t_game *g, int x, int y);
void			move_player(t_game *g, t_cam *c, int keycode);
void			rotate_player(t_cam *c, int keycode);
void			turn_player_to(t_cam *c, int dir);
void			tp_player_spawn(t_game *g);
void			switch_slots(t_game *g, int keycode);

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
unsigned int	get_time(void);
int				int_len(long n);
int				ft_max(int a, int b);
int				is_collision(char c);
int				is_castable(char c);
int				is_transparent(char c);
int				is_bounds(t_game *g, int x, int y);
int				is_sprite(char c);
void			raycast_step(t_cam *c);
int				get_dir(t_cam *c);
t_coll			*append_colls(t_coll *old, t_cam *c, t_game *g);
int				get_texture_spr(t_game *g, t_sprite spr);

#endif // CUB3D_BONUS_H
