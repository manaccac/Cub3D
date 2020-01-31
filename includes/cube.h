/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cube.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: manaccac <manaccac@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/30 08:29:10 by manaccac     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/31 12:10:08 by manaccac    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# define screenWidth	1920
# define screenHeight	1080

#include "../minilibx_opengl_20191021/mlx.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct s_img
{
	int bpp;
	int endian;
	int sizeline;
	unsigned int img_color;
	char *data;
}	t_img;

typedef struct s_color
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
}				t_color;


typedef	struct	s_player
{
	double posY;
	double posX;
	double dirX;
	double dirY;
	double cameraX;
	double planeX;
	double planeY;
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

typedef	struct	s_map
{
	void *mlx_ptr;
	void *win_ptr;
	void *img_ptr;
	t_img img;
}				t_map;

double raycasting(t_player player, int x);

#endif
