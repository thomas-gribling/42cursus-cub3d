/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 08:10:05 by tgriblin          #+#    #+#             */
/*   Updated: 2024/10/02 08:44:28 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <string.h>
# include <pulse/simple.h>
# include <pulse/error.h>
# include <sys/time.h>
# include "gnl.h"
# include "../mlx/mlx.h"

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

# define TEX_AMT 93
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
# define TEX_BUSH_BACKROOMS 11
# define TEX_WALL_OUTSIDE 12
# define TEX_WINDOW_OUTSIDE 13
# define TEX_DOOR_C_OUTSIDE 14
# define TEX_DOOR_O_OUTSIDE 15
# define TEX_WALL_BSMT 16
# define TEX_WALL_SIGN_BSMT 17
# define TEX_WINDOW_BSMT 18
# define TEX_DOOR_C_BSMT 19
# define TEX_DOOR_O_BSMT 20
# define TEX_WALL_BACKROOMS 21
# define TEX_FLOOR 22
# define TEX_FLOOR_TRAPDOOR 23
# define TEX_GROUND 24
# define TEX_GROUND_BACKROOMS 25
# define TEX_GRASS 26
# define TEX_CARPET 27
# define TEX_CEILING 28
# define TEX_CEILING_TRAPDOOR 29
# define TEX_SPR_TREE_0 30
# define TEX_SPR_TREE_1 31
# define TEX_GUI_INV_EMPTY_0 32
# define TEX_GUI_INV_EMPTY_1 33
# define TEX_GUI_INV_FULL_0 34
# define TEX_GUI_INV_FULL_1 35
# define TEX_GUI_INV_BB10_0 36
# define TEX_GUI_INV_BB10_1 37
# define TEX_GUI_INV_BB01_0 38
# define TEX_GUI_INV_BB01_1 39
# define TEX_GUI_INV_BB11_0 40
# define TEX_GUI_INV_BB11_1 41
# define TEX_GUI_0 42
# define TEX_GUI_1 43
# define TEX_GUI_2 44
# define TEX_GUI_3 45
# define TEX_GUI_4 46
# define TEX_GUI_5 47
# define TEX_GUI_6 48
# define TEX_GUI_7 49
# define TEX_GUI_8 50
# define TEX_GUI_9 51
# define TEX_GUI_SEP 52
# define TEX_GUI_MAPWALL 53
# define TEX_GUI_MAPPLAYER 54
# define TEX_GUI_MAPBULLY 55
# define TEX_GUI_MAPEXIT 56
# define TEX_GUI_SPLASH_0 57
# define TEX_GUI_SPLASH_1 58
# define TEX_GUI_SPLASH_2 59
# define TEX_GUI_SPLASH_3 60
# define TEX_PORTAL_0 61
# define TEX_PORTAL_1 62
# define TEX_NPC_JERAU 63
# define TEX_NPC_PIRATE_0 64
# define TEX_NPC_PIRATE_1 65
# define TEX_NPC_PIRATE_2 66
# define TEX_NPC_PIRATE_3 67
# define TEX_NPC_PIRATE_4 68
# define TEX_NPC_PIRATE_5 69
# define TEX_NPC_PIRATE_6 70
# define TEX_NPC_PIRATE_7 71
# define TEX_NPC_POULET 72
# define TEX_NPC_STUDENT_F_0 73
# define TEX_NPC_STUDENT_F_1 74
# define TEX_NPC_STUDENT_B_0 75
# define TEX_NPC_STUDENT_B_1 76
# define TEX_NPC_STUDENT_DEAD 77
# define TEX_NPC_BULLY_F_0 78
# define TEX_NPC_BULLY_F_1 79
# define TEX_NPC_BULLY_B_0 80
# define TEX_NPC_BULLY_B_1 81
# define TEX_NPC_BULLY_DEAD 82
# define TEX_NPC_CHAD_H 83
# define TEX_NPC_CHAD_I 84
# define TEX_NPC_CHAD_A 85
# define TEX_NPC_CHAD_D 86
# define TEX_END_0_BG 87
# define TEX_END_1_BG 88
# define TEX_END_2_BG 89
# define TEX_END_3_BG 90
# define TEX_END_4_BG 91
# define TEX_END_5_BG 92

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
	double	dist;
	int		dirx;
	int		diry;
	int		id;
}				t_enemy;

# define STUDENT 0
# define BULLY 1
# define NEXTBOT_1 2
# define NEXTBOT_2 3
# define NEXTBOT_3 4

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
	int		x;
	int		map_x;
	int		map_y;
	int		side;
	int		solid;
	double	dist;
	t_tex	tex;
	double	ray_dir_x;
	double	ray_dir_y;
	int		step_x;
	int		step_y;
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

typedef struct s_actor
{
	int		type;
	void	*ptr;
}			t_actor;

# define WALL 0
# define SPRITE 1
# define ENEMY 2

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
	t_enemy			*enemies;
	int				enemies_amt;
	int				bullies_amt;
	t_actor			*z_buffer;
	int				z_buffer_size;
	int				hide_bullies_amt;
	int				looking_x;
	int				looking_y;
	int				side;
	double			ray_dir_x;
	double			ray_dir_y;
	int				ending;
	int				id_shootable;
	int				time_m;
}				t_game;

t_map			*load_map(char *path);

void			init_values(t_game *g);
void			generate_enemies(t_game *g, int difficulty);
void			update_enemies(t_game *g);
void			free_enemies(t_game *g);
void			shoot_enemy(t_game *g);

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
void			raycast_tex(t_game *g, t_cam *c, int x, t_coll co);
void			raycast_floor_ceiling(t_game *g, t_cam *c);
void			raycast_z_buffer(t_game *g);
void			raycast_sprite(t_game *g, t_cam *c, int i);
void			raycast_enemy(t_game *g, t_cam *c, int i);
int				is_portal(t_game *g, int x, int y);
void			draw_minimap(t_game *g, t_cam *c);
int				get_texture(t_game *g, int x, int y);
void			move_player(t_game *g, t_cam *c, int keycode);
void			rotate_player(t_cam *c, int keycode);
void			turn_player_to(t_cam *c, int dir);
void			tp_player_spawn(t_game *g);

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
int				is_transparent(t_game *g, char c);
int				is_bounds(t_game *g, int x, int y);
int				is_sprite(char c);
void			raycast_step(t_cam *c);
int				get_dir(t_cam *c);
int				get_texture_spr(t_game *g, t_sprite spr);
double			dist_to_tile(t_game *g, double x, double y);
double			dist_enemy(t_game *g, int i, double x, double y);
t_coll			*dup_coll(t_coll *old, t_cam *c);

void			fill_z_buffer(t_game *g);
void			append_z_buffer(t_game *g, void *ptr, int type);
void			free_z_buffer(t_game *g);

void			playsound(char *file, int wait, int stop, int attenued);

#endif // CUB3D_BONUS_H
