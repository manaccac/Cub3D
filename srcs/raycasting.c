/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   raycasting.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: manaccac <manaccac@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/30 08:38:04 by manaccac     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/30 09:31:31 by manaccac    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/cube.h"

int		ft_close(t_map *map)
{
	mlx_clear_window(map->mlx_ptr, map->win_ptr);
	mlx_destroy_window(map->mlx_ptr, map->win_ptr);
	exit (EXIT_SUCCESS);
	return (0);
}
int		ft_key(int key, t_map *map)
{
	if (key == 53)
		ft_close(map);
	return (0);
}

t_player ft_init_player(void)
{
  t_player player;

  player.posY = 12;
  player.posX = 22;
  player.dirX = -1;
  player.dirY = 0;
  player.planeX = 0;
  player.planeY = 0.66;
}

int   ft_abs(nb)
{
  if (nb >= 0)
    return (nb);
  return (-nb);
}

int raycasting(t_map map)
{
  t_player player;
  t_calray calray;

  player = ft_init_player();
  map.img_ptr = mlx_new_image(map.mlx_ptr, 1280, 1080);
	map.win_ptr = mlx_new_window(map.mlx_ptr, screenWidth, screenHeight, "cub3d" );
    for(int x = 0; x < screenWidth; x++)
    {
      //calculate ray position and direction
      player.cameraX = 2 * x / (double)screenWidth - 1; //x-coordinate in camera space
      calray.rayDirX = player.dirX + player.planeX * player.cameraX;
      calray.rayDirY = player.dirY + player.planeY * player.cameraX;
      //which box of the map we're in
    calray.mapX = player.posX;
    calray.mapY = player.posY;

    calray.deltaDistX = ft_abs(1 / calray.rayDirX);
    calray.deltaDistY = ft_abs(1 / calray.rayDirY);

    calray.hit = 0; //was there a wall hit?
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
     //perform DDA
     while (calray.hit == 0)
     {
       //jump to next map square, OR in x-direction, OR in y-direction
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
       //Check if ray has hit a wall
       if(worldMap[mapX][mapY] > 0)
	      calray.hit = 1;
    }
     //Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
     if(calray.side == 0)
      calray.perpWallDist = (calray.mapX - player.posX + (1 - calray.stepX) / 2) / calray.rayDirX;
     else
      calray.perpWallDist = (calray.mapY - player.posY + (1 - calray.stepY) / 2) / calray.rayDirY;
     calray.lineHeight = (int)(screenHeight / calray.perpWallDist);
     calray.drawStart = -calray.lineHeight / 2 + screenHeight / 2;
     if(calray.drawStart < 0)
      calray.drawStart = 0;
     calray.drawEnd = calray.lineHeight / 2 + screenHeight / 2;
     if(calray.drawEnd >= screenHeight)
      calray.drawEnd = screenHeight - 1;
  //draw the pixels of the stripe as a vertical line
  verLine(x, drawStart, drawEnd, color);
 }
  mlx_hook(map.win_ptr, 2, 0, ft_key, &map);
  mlx_hook(map.win_ptr, 17, 0, ft_close, &map);
  mlx_loop(map.mlx_ptr);
}
