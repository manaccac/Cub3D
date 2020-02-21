/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cube.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: manaccac <manaccac@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/31 08:56:54 by manaccac     #+#   ##    ##    #+#       */
/*   Updated: 2020/02/21 08:00:32 by manaccac    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/cube.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const unsigned char	*src2;
	unsigned char		*dst2;

	if (!dst && !src)
		return (NULL);
	src2 = src;
	dst2 = dst;
	while (n-- > 0)
		*dst2++ = *src2++;
	return (dst);
}

int		ft_close(t_map *map)
{
	mlx_clear_window(map->mlx_ptr, map->win_ptr);
	mlx_destroy_window(map->mlx_ptr, map->win_ptr);
	exit (EXIT_SUCCESS);
	return (0);
}

int ft_walkforward(t_map *map)
{
	map->player.mouveX += map->player.dirX * 0.15 * map->player.movew;
	map->player.mouveY += map->player.dirY * 0.15 * map->player.movew;
	return(0);
}

int ft_walkbackward(t_map *map)
{
	map->player.mouveX -= map->player.dirX * 0.15 * map->player.moves;
	map->player.mouveY -= map->player.dirY * 0.15 * map->player.moves;
	return(0);
}

int ft_walkleft(t_map *map)
{
	map->player.mouveX -= map->player.planeX * 0.15 * map->player.movea;
	map->player.mouveY -= map->player.planeY * 0.15 * map->player.movea;
	return(0);
}

int ft_walkright(t_map *map)
{
	map->player.mouveX += map->player.planeX * 0.15 * map->player.moved;
	map->player.mouveY += map->player.planeY * 0.15 * map->player.moved;
	return(0);
}

int	ft_turnright(t_map *map)
{
	double pi = 3.14159265359;
	double speed = 2*pi/90;
	double oldDirX = map->player.dirX;
	double oldPlaneX = map->player.planeX;
	map->player.dirX = map->player.dirX * cos(-speed * map->player.key_e) - map->player.dirY * sin(-speed * map->player.key_e);
	map->player.dirY = oldDirX * sin(-speed * map->player.key_e) + map->player.dirY * cos(-speed * map->player.key_e);
	map->player.planeX = map->player.planeX * cos(-speed * map->player.key_e) - map->player.planeY * sin(-speed * map->player.key_e);
    map->player.planeY = oldPlaneX * sin(-speed * map->player.key_e) + map->player.planeY * cos(-speed * map->player.key_e);
	return(0);
}

int	ft_turnleft(t_map *map)
{
	double pi = 3.14159265359;
	double speed = 2*pi/90;
	double oldDirX = map->player.dirX;
	double oldPlaneX = map->player.planeX;
	map->player.dirX = map->player.dirX * cos(speed * map->player.key_q) - map->player.dirY * sin(speed * map->player.key_q);
    map->player.dirY = oldDirX * sin(speed * map->player.key_q) + map->player.dirY * cos(-speed * map->player.key_q);
	map->player.planeX = map->player.planeX * cos(speed * map->player.key_q) - map->player.planeY * sin(speed * map->player.key_q);
    map->player.planeY = oldPlaneX * sin(speed * map->player.key_q) + map->player.planeY * cos(speed * map->player.key_q);
	return(0);
}

t_map ft_init_player(void)
{
	t_map map;

	map.player.posY = 12;
	map.player.posX = 22;
	map.player.dirX = -1;
	map.player.dirY = 0;
	map.player.planeX = 0;
	map.player.planeY = 0.66;
	map.player.movew = 0;
	map.player.moved = 0;
	map.player.moves = 0;
	map.player.movea = 0;
	map.player.key_e = 0;
	map.player.key_q = 0;
  return (map);
}

void ft_vertline(int h, int x, t_map map)
{
	int y;
	unsigned int color;
	t_color clr;

	y = 0;
	if (h == -1)
		return;
	int floor = (screenHeight - h) /2;
	int sky = floor;

	if(map.wall_dir == 'W' || map.wall_dir == 'E')
		map.textx = (map.hit_wall_x - (int)map.hit_wall_x) * 64;
	else if (map.wall_dir == 'N' || map.wall_dir == 'S')
		map.textx = (map.hit_wall_y - (int)map.hit_wall_y) * 64;
	while (y < screenHeight)
	{
		if (y <= floor)
			map.img.data[x + y * screenWidth] = 0x2880BB;
		else if(y < (screenHeight - sky) && y > floor)
		{
			int i = y * screenWidth + x;
			map.texty = ((double)y - (double)sky)/(double)(screenHeight  - sky - floor) * 64;
			int it = (int)(map.texty) * map.texture[map.wall_text].sizeline/4 + (int)(map.textx);
    		map.img.data[y * screenWidth + x] = map.texture[map.wall_text].data[it];
		}
		else
			map.img.data[x + y * screenWidth] = 0x655E57;
		y++;
	}
}

int	ft_printwall(t_map map)
{
	double ray_dist;
	int h;
	int x;

	x = 0;
	while (x < screenWidth)
    {
		map.img.img_color = mlx_get_color_value(map.mlx_ptr, 0xffffff);
		ray_dist = raycasting(map.player, x, &map);
		h =(int)(screenHeight / ray_dist);
		ft_vertline(h, x, map);
    	x++;
    }
	mlx_put_image_to_window (map.mlx_ptr, map.win_ptr, map.img_ptr, 0, 0);
	return 1;
}

int		ft_i_walk(t_map *map)
{
	mlx_clear_window(map->mlx_ptr, map->win_ptr);
	map->player.mouveX = 0;
	map->player.mouveY = 0;

	if (map->player.movew)
		ft_walkforward(map);
	if (map->player.moved)
		ft_walkright(map);
	if (map->player.moves)
		ft_walkbackward(map);
	if (map->player.movea)
		ft_walkleft(map);
	if (map->player.key_e)
		ft_turnright(map);
	if (map->player.key_q)
		ft_turnleft(map);
	map->player.posX = map->player.posX + map->player.mouveX;
	map->player.posY = map->player.posY + map->player.mouveY;
	//dprintf(1, "X= %f Y= %f\n", map->player.posX , map->player.posY);
	ft_printwall(*map);
	return (0);
}

int		ft_keyp(int key, t_map *map)
{
	if (key == KEY_W)
		map->player.movew = 1;
	if (key == KEY_D)
		map->player.moved = 1;
	if (key == KEY_S)
		map->player.moves = 1;
	if (key == KEY_A)
		map->player.movea = 1;
	if (key == KEY_E)
		map->player.key_e = 1;
	if (key == KEY_Q)
		map->player.key_q = 1;
	if (key == 53)
		ft_close(map);
	return (0);
}

int		ft_keyr(int key, t_map *map)
{
	if (key == KEY_W)
		map->player.movew = 0;
	if (key == KEY_D)
		map->player.moved = 0;
	if (key == KEY_S)
		map->player.moves = 0;
	if (key == KEY_A)
		map->player.movea = 0;
	if (key == KEY_E)
		map->player.key_e = 0;
	if (key == KEY_Q)
		map->player.key_q = 0;
	return (0);
}

/*
t_map ft_init_texture(t_map *map)
{
	int i;

	i = 0;
	while (i != 4)
	{
		map->texture[i].bpp = 0;
		map->texture[i].sizeline = 0;
		map->texture[i].endian = 0;
		i++;
	}
	return (*map);
}

*/
t_map	ft_texture(t_map map)
{
	map.texture[0].image = mlx_xpm_file_to_image(map.mlx_ptr, "textures/colorstone.xpm", &map.texture[0].width, &map.texture[0].height);
	map.texture[0].data = (int*)mlx_get_data_addr(map.texture[0].image, &map.texture[0].bpp, &map.texture[0].sizeline, &map.texture[0].endian);
	map.texture[1].image = mlx_xpm_file_to_image(map.mlx_ptr, "textures/greystone.xpm", &map.texture[1].width, &map.texture[1].height);
	map.texture[1].data = (int*)mlx_get_data_addr(map.texture[1].image, &map.texture[1].bpp, &map.texture[1].sizeline, &map.texture[1].endian);
	map.texture[2].image = mlx_xpm_file_to_image(map.mlx_ptr, "textures/mossy_1.xpm", &map.texture[2].width, &map.texture[2].height);
	map.texture[2].data = (int*)mlx_get_data_addr(map.texture[2].image, &map.texture[2].bpp, &map.texture[2].sizeline, &map.texture[2].endian);
	map.texture[3].image = mlx_xpm_file_to_image(map.mlx_ptr, "textures/redbrick_1.xpm", &map.texture[3].width, &map.texture[3].height);
	map.texture[3].data = (int*)mlx_get_data_addr(map.texture[3].image, &map.texture[3].bpp, &map.texture[3].sizeline, &map.texture[3].endian);
	return	(map);
}


int	main() //void	cube()
{
	t_map map;

	map = ft_init_player();

 	map.mlx_ptr = mlx_init();
	map = ft_texture(map);
//	map.texture[0].image = mlx_xpm_file_to_image(map.mlx_ptr, "textures/colorstone.xpm", &map.texture[0].width, &map.texture[0].height);
//	map.texture[0].data = mlx_get_data_addr(map.texture[0].image, &map.texture[0].bpp, &map.texture[0].sizeline, &map.texture[0].endian);

	map.win_ptr = mlx_new_window(map.mlx_ptr, screenWidth, screenHeight, "CUBE");

	map.img_ptr = mlx_new_image(map.mlx_ptr, screenWidth, screenHeight);
	map.img.data = (int*)mlx_get_data_addr(map.img_ptr, &map.img.bpp, &map.img.sizeline, &map.img.endian);
	map.win_ptr = mlx_new_window(map.mlx_ptr, screenWidth, screenHeight, "CUBE");

	ft_printwall(map);

	mlx_hook(map.win_ptr, 2, 0, ft_keyp, &map);
	mlx_hook(map.win_ptr, 3, 0, ft_keyr, &map);
	mlx_hook(map.win_ptr, 17, 0, ft_close, &map);
	mlx_loop_hook(map.mlx_ptr, ft_i_walk, &map);
	mlx_loop(map.mlx_ptr);

	return(0);
}
