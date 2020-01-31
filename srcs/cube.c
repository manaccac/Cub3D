/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cube.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: manaccac <manaccac@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/31 08:56:54 by manaccac     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/31 11:59:29 by manaccac    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/cube.h"

t_color ft_color(int r, int g, int b)
{
	t_color color;
	color.r = (unsigned char)r;
	color.g = (unsigned char)g;
	color.b = (unsigned char)b;
	return(color);
}

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
  return (player);
}

void    my_pixel_put_to_image(t_color color, char *data, int sizeline, int bpp, int x, int y)
{
  data[y * sizeline + x * bpp / 8 ] = color.r;
  data[y * sizeline + x * bpp / 8 + 1] = color.g;
  data[y * sizeline + x * bpp / 8 + 2] = color.b;
}

void ft_vertline(int h, int x, t_map map)
{
	int y;

	y = 0;
	if (h == -1)
		return;
	int floorsize = (screenHeight - h) /2;
	int skysize = floorsize;
	while (y < screenHeight)
	{
		if (y < floorsize)
			my_pixel_put_to_image(ft_color(172, 96, 35), map.img.data, map.img.sizeline, map.img.bpp, x, y);
		else if(y < (screenHeight - skysize) && y > floorsize)
			my_pixel_put_to_image(ft_color(58, 136, 189), map.img.data, map.img.sizeline, map.img.bpp, x, y);
		else
			my_pixel_put_to_image(ft_color(105, 34, 144), map.img.data, map.img.sizeline, map.img.bpp, x, y);
		y++;
	}
}

int	ft_PrintWall(t_map map, t_player player)
{
	double ray_dist;
	int h;
	int x;
	x = 0 ;

	while (x < screenWidth)
    {
		map.img.img_color = mlx_get_color_value(map.mlx_ptr, 0xffffff);
		ray_dist = raycasting(player, x);
		h =(int)(screenHeight / ray_dist);
		ft_vertline(h, x, map);
    	x++;
    }
	mlx_put_image_to_window (map.mlx_ptr, map.win_ptr, map.img_ptr, 0, 0);
	return 1;
}

int	main() //void	cube()
{
	t_player player;
	t_map map;

	player = ft_init_player();
 	map.mlx_ptr = mlx_init();
	map.img_ptr = mlx_new_image(map.mlx_ptr, screenWidth, screenHeight);
  	map.img.data = mlx_get_data_addr(map.img_ptr, &map.img.bpp, &map.img.sizeline, &map.img.endian);
	map.win_ptr = mlx_new_window(map.mlx_ptr, screenWidth, screenHeight, "CUBE");

	ft_PrintWall(map, player);

	mlx_hook(map.win_ptr, 2, 0, ft_key, &map);
	mlx_hook(map.win_ptr, 17, 0, ft_close, &map);
	mlx_loop(map.mlx_ptr);
	return(0);
}
