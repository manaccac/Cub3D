/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manaccac <manaccac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 08:29:10 by manaccac          #+#    #+#             */
/*   Updated: 2020/07/14 10:39:04 by manaccac         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUBE_H
# define CUBE_H

# include "../libft/libft.h"
#include "../minilibx_opengl_20191021/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
# include <unistd.h>
#include <fcntl.h>

typedef struct s_img
{
	int bpp;
	int endian;
	int sizeline;
	unsigned int img_color;
	int *data;
}	t_img;

typedef struct s_color
{
	int r;
	int g;
	int b;
	int a;
	int	color;
}				t_color;

typedef	struct	s_texture
{
	void		*image;
	int			*data;
	int			bpp;
	int			sizeline;
	int			endian;
	int			width;
	int 		height;
	char		*textpath;
}				t_texture;

typedef	struct	s_mouvperm
{
	int	x;
	int	y;
}		t_mouvperm;

typedef	struct	s_player
{
	double 	posY;
	double 	posX;
	double 	dirX;
	double 	dirY;
	double 	cameraX;
	double 	planeX;
	double 	planeY;
	int		movew;
	int		moved;
	int		moves;
	int		movea;
	int		key_e;
	int		key_q;
	double 	mouveX;
	double	mouveY;
}				t_player;

typedef struct s_calray
{
	double rayDirX;
	double rayDirY;
	int mapX;
	int mapY;
	double sideDistX;
	double sideDistY;
	double deltaDistX;
	double deltaDistY;
	double perpWallDist;
	int stepX;
	int stepY;
	int hit;
	int side;
	int lineHeight;
	int drawStart;
	int drawEnd;
}	t_calray;

typedef struct		s_text_spr
{
	void			*image;
	int				width;
	int				height;
	int				*img_data;
	int				bpp;
	int				sizeline;
	int				endian;
	char			*textpath;
}					t_text_spr;

typedef struct s_sprcal
{
	int		nbspr;
	double spritex;
	double spritey;
	double invdet;
	double transformx;
	double transformy;
	int spritescreenx;
}	t_sprcal;

typedef	struct	s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef	struct	s_vector_int
{
	int		x;
	int		y;
}	t_vector_int;

typedef	struct	s_sprites
{
	double	dist;
	double	posx;
	double	posy;
}	t_sprites;

typedef struct	s_draw_start
{
	int	x;
	int	y;
}	t_draw_start;

typedef struct	s_draw_end
{
	int	x;
	int	y;
}	t_draw_end;

typedef struct s_pars
{
	char	*temp;
	int		twidth;
	int		width;
	int		height;
	char	*str;
	int		x;
	int		y;
	int		perm;
	char			*width_str;
	char			*height_str;
	int				ground_r;
	int				ground_g;
	int				ground_b;
	int				sky_r;
	int				sky_g;
	int				sky_b;
	char			*temp_two;
}				t_pars;

typedef struct	s_bitmap_file_header
{
	unsigned char	bitmap_type[2];
	int				file_size;
	short			reserved1;
	short			reserved2;
	unsigned int	offset_bits;
}				t_bfh;

typedef struct	s_bitmap_image_header
{
	unsigned int	size_header;
	unsigned int	width;
	unsigned int	height;
	short int		planes;
	short int		bit_count;
	unsigned int	compression;
	unsigned int	image_size;
	unsigned int	ppm_x;
	unsigned int	ppm_y;
	unsigned int	clr_used;
	unsigned int	clr_important;
}				t_bih;

typedef struct	s_sprt
{
	int j;
	double swapx;
	double swapy;
	double dist;
}				t_sprt;

typedef	struct	s_map
{
	void *mlx_ptr;
	void *win_ptr;
	void *img_ptr;
	t_player player;
	t_img img;
	t_sprt sprt;
	char 	*text_north;
	char	*text_east;
	char	*text_south;
	char	*text_west;
	double	hit_wall_x;
	double	hit_wall_y;
	double textx;
	double texty;
	char	wall_dir;
	int wall_text;
	int		nb_sprites;
	t_texture texture[4];
	t_vector sprite;
	t_sprites sprites[50];
	t_vector transform;
	double	inv_det;
	int		sprite_screen_x;
	int		sprite_height;
	int		sprite_width;
	int		stripe;
	int		tex_x;
	int		tex_y;
	t_draw_start draw_start;
	t_draw_end draw_end;
	t_text_spr text_spr;
	double		*zbuffer;
	t_mouvperm mouvperm;
	t_pars		pars;
	int			**worldmap;
	int			scwidth;
	int			scheight;
	int				error;
	int				error_parsing;
	char			*cub;

	t_vector_int	map_pars;
	char			**map_temp;
	int		a;
	int		b;

}				t_map;

int				ft_parsing_map(t_map *map);
void	ft_raycasting_sprite(t_map *map);
double raycasting(t_player player, int x, t_map *map);
int				ft_ground_sky(char *str, int i, t_map *map);
int				ft_find(const char c, const char *str);
int				ft_puterror(t_map *map, char *str);
int				ft_parsing(t_map *map);
int				ft_read_map(t_map *map);
int				ft_check_parsing(t_map *map);
void			ft_putchar_v(char c);
void			ft_putstr_v(char *str);
char			*ft_parsing_texture(char *s, t_map *map);
int				ft_parsing_resolution(char *s, t_map *map);
int				ft_parsing_ground_sky_two(char *str, int i, t_map *map);
void			ft_recover_sprite(t_map *map);
int				ft_fill_map(t_map *map);
int				ft_check_map(t_map *map);
int				ft_check_map_char(char *str);
int				ft_parsing_ground_sky(char *s, t_map *map);
int				ft_resolution_two(char *str, t_map *map, int i, int j);
int				ft_parsing_start(char *s, t_map *map);
void                    ft_recover_sprite_two(t_map *map, int x, int y, int i);
int				ft_check_wall(int x, int y, t_map *map);
int		ft_check_cub(char	*str);
int		ft_check_save(char	*str);
void	save_bitmap(const char *filename, t_map *map);

# define KEY_ESCAPE         53
# define KEY_F1             122
# define KEY_F2             120
# define KEY_F3             99
# define KEY_F4             118
# define KEY_F5             96
# define KEY_F6             97
# define KEY_F7             98
# define KEY_F8             100
# define KEY_F9             101
# define KEY_F10            109
# define KEY_F11            103
# define KEY_F12            111
# define KEY_F13            105
# define KEY_F14            107
# define KEY_F15            113
# define KEY_F16            106
# define KEY_F17            64
# define KEY_F18            79
# define KEY_F19            80
# define KEY_TILDE          50
# define KEY_1              18
# define KEY_2              19
# define KEY_3              20
# define KEY_4              21
# define KEY_5              23
# define KEY_6              22
# define KEY_7              26
# define KEY_8              28
# define KEY_9              25
# define KEY_0              29
# define KEY_MINUS          27
# define KEY_EQUAL          24
# define KEY_BACKSPACE      51
# define KEY_TAB            48
# define KEY_Q              12
# define KEY_W              13
# define KEY_E              14
# define KEY_R              15
# define KEY_T              17
# define KEY_Y              16
# define KEY_U              32
# define KEY_I              34
# define KEY_O              31
# define KEY_P              35
# define KEY_OPEN_BRACKET   33
# define KEY_OPEN_BRACE     33
# define KEY_CLOSE_BRACKET  30
# define KEY_CLOSE_BRACE    30
# define KEY_BACKSLASH      42
# define KEY_PIPE           42
# define KEY_CAPSLOCK       272
# define KEY_A              0
# define KEY_S              1
# define KEY_D              2
# define KEY_F              3
# define KEY_G              5
# define KEY_H              4
# define KEY_J              38
# define KEY_K              40
# define KEY_L              37
# define KEY_COLON          41
# define KEY_SEMI_COLON     41
# define KEY_SIMPLE_QUOTE   39
# define KEY_DOUBLE_QUOTES  39
# define KEY_ENTER          36
# define KEY_SHIFT_LEFT     257
# define KEY_Z              6
# define KEY_X              7
# define KEY_C              8
# define KEY_V              9
# define KEY_B              11
# define KEY_N              45
# define KEY_M              46
# define KEY_LESS_THAN      43
# define KEY_COMMA          43
# define KEY_GREATER_THAN   47
# define KEY_DOT            47
# define KEY_SLASH          44
# define KEY_QUESTION_MARK  44
# define KEY_SHIFT_RIGHT    258
# define KEY_CTRL_LEFT      256
# define KEY_COMMAND_LEFT   259
# define KEY_OPTION_LEFT    261
# define KEY_ALT            261
# define KEY_SPACEBAR       49
# define KEY_COMMAND_RIGHT  260
# define KEY_ALT_GR         262
# define KEY_FN             279
# define KEY_CTRL_RIGHT     269
# define KEY_LEFT           123
# define KEY_DOWN           125
# define KEY_RIGHT          124
# define KEY_UP             126
# define KEY_DEL            117
# define KEY_HOME           115
# define KEY_END            119
# define KEY_PAGE_UP        116
# define KEY_PAGE_DOWN      121
# define KEY_CLEAR          71
# define KEY_PAD_1          83
# define KEY_PAD_2          84
# define KEY_PAD_3          85
# define KEY_PAD_4          86
# define KEY_PAD_5          87
# define KEY_PAD_6          88
# define KEY_PAD_7          89
# define KEY_PAD_8          91
# define KEY_PAD_9          92
# define KEY_PAD_0          82
# define KEY_PAD_EQUAL      81
# define KEY_PAD_DIVIDE     75
# define KEY_PAD_MULTIPLY   67
# define KEY_PAD_SUB        78
# define KEY_PAD_ADD        69
# define KEY_PAD_ENTER      76
# define KEY_PAD_DOT        65

#endif
