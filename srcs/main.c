/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manaccac <manaccac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 08:56:54 by manaccac          #+#    #+#             */
/*   Updated: 2020/07/14 20:04:49 by manaccac         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

t_mouvperm		ft_colision(t_map map)
{
	t_mouvperm mouvperm;

	if (map.worldmap[(int)map.player.posX]
		[(int)(map.player.mouveY + map.player.posY)] == 1)
		mouvperm.y = 0;
	else
		mouvperm.y = 1;
	if (map.worldmap[(int)(map.player.mouveX + map.player.posX)]
		[(int)map.player.posY] == 1)
		mouvperm.x = 0;
	else
		mouvperm.x = 1;
	return (mouvperm);
}

void		*ft_memcpy(void *dst, const void *src, size_t n)
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

int			ft_close(t_map *map)
{
	mlx_clear_window(map->mlx_ptr, map->win_ptr);
	mlx_destroy_window(map->mlx_ptr, map->win_ptr);
	exit(EXIT_SUCCESS);
	return (0);
}

int			ft_walkforward(t_map *map)
{
	map->player.mouveX += map->player.dirX * 0.15 * map->player.movew;
	map->player.mouveY += map->player.dirY * 0.15 * map->player.movew;
	return (0);
}

int			ft_walkbackward(t_map *map)
{
	map->player.mouveX -= map->player.dirX * 0.15 * map->player.moves;
	map->player.mouveY -= map->player.dirY * 0.15 * map->player.moves;
	return (0);
}

int			ft_walkleft(t_map *map)
{
	map->player.mouveX -= map->player.planeX * 0.15 * map->player.movea;
	map->player.mouveY -= map->player.planeY * 0.15 * map->player.movea;
	return (0);
}

int			ft_walkright(t_map *map)
{
	map->player.mouveX += map->player.planeX * 0.15 * map->player.moved;
	map->player.mouveY += map->player.planeY * 0.15 * map->player.moved;
	return (0);
}

int			ft_turnright(t_map *map)
{
	double pi;
	double speed;
	double olddirx;
	double oldplanex;

	pi = 3.14159265359;
	speed = 2 * pi / 90;
	olddirx = map->player.dirX;
	oldplanex = map->player.planeX;
	map->player.dirX = map->player.dirX * cos(-speed * map->player.key_e)
		- map->player.dirY * sin(-speed * map->player.key_e);
	map->player.dirY = olddirx * sin(-speed * map->player.key_e)
		+ map->player.dirY * cos(-speed * map->player.key_e);
	map->player.planeX = map->player.planeX * cos(-speed *
		map->player.key_e) - map->player.planeY *
		sin(-speed * map->player.key_e);
	map->player.planeY = oldplanex * sin(-speed * map->player.key_e)
		+ map->player.planeY * cos(-speed * map->player.key_e);
	return (0);
}

int			ft_turnleft(t_map *map)
{
	double pi;
	double speed;
	double olddirx;
	double oldplanex;

	pi = 3.14159265359;
	speed = 2 * pi / 90;
	olddirx = map->player.dirX;
	oldplanex = map->player.planeX;
	map->player.dirX = map->player.dirX * cos(speed * map->player.key_q)
		- map->player.dirY * sin(speed * map->player.key_q);
	map->player.dirY = olddirx * sin(speed * map->player.key_q)
		+ map->player.dirY * cos(-speed * map->player.key_q);
	map->player.planeX = map->player.planeX * cos(speed *
		map->player.key_q) - map->player.planeY *
		sin(speed * map->player.key_q);
	map->player.planeY = oldplanex * sin(speed *
		map->player.key_q) + map->player.planeY *
		cos(speed * map->player.key_q);
	return (0);
}

t_map		ft_if_verline(t_map map)
{
	if (map.wall_dir == 'W' || map.wall_dir == 'E')
		map.textx = (map.hit_wall_x - (int)map.hit_wall_x) * 64;
	else if (map.wall_dir == 'N' || map.wall_dir == 'S')
		map.textx = (map.hit_wall_y - (int)map.hit_wall_y) * 64;
	return (map);
}

void		ft_vertline(int h, int x, t_map map)
{
	int				y;
	int				notwall;
	int				it;

	y = -1;
	if (h == -1)
		return ;
	notwall = (map.scheight - h) / 2;
	map = ft_if_verline(map);
	while (++y < map.scheight)
	{
		if (y <= notwall)
			map.img.data[x + y * map.scwidth] = 0x2880BB;
		else if (y < (map.scheight - notwall) && y > notwall)
		{
			map.texty = ((double)y - (double)notwall) /
				(double)(map.scheight - notwall - notwall) * 64;
			it = (int)(map.texty) * map.texture[map.wall_text].sizeline /
				4 + (int)(map.textx);
			map.img.data[y * map.scwidth + x] =
				map.texture[map.wall_text].data[it];
		}
		else
			map.img.data[x + y * map.scwidth] = 0x585551;
	}
}

int			ft_printwall(t_map map)
{
	double	ray_dist;
	int		h;
	int		x;

	x = 0;
	while (x < map.scwidth)
	{
		map.img.img_color = mlx_get_color_value(map.mlx_ptr, 0xffffff);
		ray_dist = raycasting(map.player, x, &map);
		h = (int)(map.scheight / ray_dist);
		ft_vertline(h, x, map);
		map.zbuffer[x] = ray_dist;
		x++;
	}
	ft_raycasting_sprite(&map);
	mlx_put_image_to_window(map.mlx_ptr, map.win_ptr, map.img_ptr, 0, 0);
	return (1);
}

int			ft_i_walk(t_map *map)
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
	map->mouvperm = ft_colision(*map);
	if (map->mouvperm.x)
		map->player.posX = map->player.posX + map->player.mouveX;
	if (map->mouvperm.y)
		map->player.posY = map->player.posY + map->player.mouveY;
	ft_printwall(*map);
	return (0);
}

int			ft_keyp(int key, t_map *map)
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

int			ft_keyr(int key, t_map *map)
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

t_map		ft_texture(t_map map)
{
	int	i;

	i = 0;
	while (i != 4)
	{
		map.texture[i].image = mlx_xpm_file_to_image(map.mlx_ptr,
			map.texture[i].textpath, &map.texture[i].width,
			&map.texture[i].height);
		map.texture[i].data = (int*)mlx_get_data_addr(map.texture[i].image
			, &map.texture[i].bpp,
			&map.texture[i].sizeline, &map.texture[i].endian);
		i++;
	}
	map.text_spr.image = mlx_xpm_file_to_image(map.mlx_ptr,
		map.text_spr.textpath, &map.text_spr.width, &map.text_spr.height);
	map.text_spr.img_data = (int*)mlx_get_data_addr(map.text_spr.image,
		&map.text_spr.bpp, &map.text_spr.sizeline, &map.text_spr.endian);
	return (map);
}

t_map		ft_initmap(t_map map)
{
	map.error = 0;
	map.pars.height = 0;
	map.pars.width = 0;
	map.pars.twidth = 0;
	map.pars.perm = 0;
	map.pars.x = 0;
	map.pars.y = 0;
	map.player.movew = 0;
	map.player.moved = 0;
	map.player.moves = 0;
	map.player.movea = 0;
	map.player.key_e = 0;
	map.player.key_q = 0;
	return (map);
}

int			ft_verif(int argc, char **argv, t_map map)
{
	if (argc == 3)
	{
		if (ft_check_save(argv[2]) == 0)
		{
			ft_putstr_v("To many arguments");
			return (0);
		}
		else
		{
			ft_printwall(map);
			save_bitmap("cube.bmp", &map);
			return (0);
		}
	}
	return (1);
}

t_map		ft_mapcreate(t_map map)
{
	map.zbuffer = (double *)malloc(sizeof(double) * map.scwidth);
	map.mlx_ptr = mlx_init();
	map = ft_texture(map);
	map.img_ptr = mlx_new_image(map.mlx_ptr, map.scwidth, map.scheight);
	map.img.data = (int*)mlx_get_data_addr(map.img_ptr,
		&map.img.bpp, &map.img.sizeline, &map.img.endian);
	map.win_ptr = mlx_new_window(map.mlx_ptr, map.scwidth,
		map.scheight, "CUBE");
	return (map);
}

t_map		ft_ifarg(int argc, char **argv, t_map map)
{
	if (argc >= 2)
	{
		if (ft_check_cub(argv[1]) == 0)
		{
			ft_putstr_v("Need .cub");
		}
		else
			map.cub = ft_strdup(argv[1]);
	}
	return (map);
}

int		ft_ifargerror(int argc, char **argv, t_map map)
{
	if (argc >= 2)
	{
		if (ft_check_cub(argv[1]) == 0)
		{
			ft_putstr_v("Need .cub");
			return (0);
		}
	}
	if (argc > 3)
	{
		ft_putstr_v("To many arguments");
		return (0);
	}
	return (1);
}

int			main(int argc, char **argv)
{
	t_map map;

	map = ft_initmap(map);
	map = ft_ifarg(argc, argv, map);
	if (ft_ifargerror(argc, argv, map) == 0)
		return (0);
	ft_parsing(&map);
	if (map.error == 1)
		return (0);
	ft_check_parsing(&map);
	map = ft_mapcreate(map);
	if (ft_verif(argc, argv, map) == 0)
	{
		exit(EXIT_SUCCESS);
		return (0);
	}
	ft_printwall(map);
	mlx_hook(map.win_ptr, 2, 0, ft_keyp, &map);
	mlx_hook(map.win_ptr, 3, 0, ft_keyr, &map);
	mlx_hook(map.win_ptr, 17, 0, ft_close, &map);
	mlx_loop_hook(map.mlx_ptr, ft_i_walk, &map);
	mlx_loop(map.mlx_ptr);
	return (0);
}
