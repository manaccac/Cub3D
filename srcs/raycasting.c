/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   raycasting.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: manaccac <manaccac@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/30 08:38:04 by manaccac     #+#   ##    ##    #+#       */
/*   Updated: 2020/02/20 11:35:10 by manaccac    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/cube.h"

int worldMap[24][24]=
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
	{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1},
	{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,4,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,4,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

double ft_abs(double n)
{
	if(n >= 0)
		return(n);
	return(-n);
}

char	ft_wall_dir(t_calray calray)
{
	if (calray.side == 1)
    {
      if(calray.stepY > 0)
        return('W');
      else
        return('E');
    }
    if (calray.side == 0)
    {
      if(calray.stepX > 0)
        return('S');
      else
        return('N');
    }
  return 0;
}

double raycasting(t_player player, int x, t_map *map)
{
	t_calray calray;

	player.cameraX = 2 * x / (double)screenWidth - 1;
	calray.rayDirX = player.dirX + player.planeX * player.cameraX;
	calray.rayDirY = player.dirY + player.planeY * player.cameraX;
	calray.mapX = (int)player.posX;
	calray.mapY = (int)player.posY;

	calray.deltaDistX = ft_abs(1 / calray.rayDirX);
	calray.deltaDistY = ft_abs(1 / calray.rayDirY);

	calray.side = 0;
	calray.hit = 0;
	if(calray.rayDirX < 0)
	{
		calray.stepX = -1;
		calray.sideDistX = (player.posX - calray.mapX) * calray.deltaDistX;
	}
	else
	{
		calray.stepX = 1;
		calray.sideDistX = (calray.mapX + 1.0 - player.posX) * calray.deltaDistX;
	}
	if(calray.rayDirY < 0)
	{
		calray.stepY = -1;
		calray.sideDistY = (player.posY - calray.mapY) * calray.deltaDistY;
	}
	else
	{
		calray.stepY = 1;
		calray.sideDistY = (calray.mapY + 1.0 - player.posY) * calray.deltaDistY;
	}
	while (calray.hit == 0)
	{
		if(calray.sideDistX < calray.sideDistY)
		{
			calray.sideDistX += calray.deltaDistX;
			calray.mapX += calray.stepX;
			calray.side = 0;
		}
		else
		{
			calray.sideDistY += calray.deltaDistY;
			calray.mapY += calray.stepY;
			calray.side = 1;
		}
		if(worldMap[calray.mapX][calray.mapY] > 0)
			calray.hit = 1;
	}
	if(calray.side == 0)
		calray.perpWallDist = (calray.mapX - player.posX + (1 - calray.stepX) / 2) / calray.rayDirX;
	else
		calray.perpWallDist = (calray.mapY - player.posY + (1 - calray.stepY) / 2) / calray.rayDirY;

	map->hit_wall_x = player.posX + calray.rayDirX * calray.perpWallDist;
	map->hit_wall_y = player.posY + calray.rayDirY * calray.perpWallDist;
	map->wall_dir = ft_wall_dir(calray);
	if (map->wall_dir == 'W')
		map->wall_text = 0;
	else if (map->wall_dir == 'E')
		map->wall_text = 1;
	else if (map->wall_dir == 'N')
		map->wall_text = 2;
	else if (map->wall_dir == 'S')
		map->wall_text = 3;
	return (calray.perpWallDist);
}
