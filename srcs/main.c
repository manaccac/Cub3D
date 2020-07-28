/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manaccac <manaccac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 08:56:54 by manaccac          #+#    #+#             */
/*   Updated: 2020/07/19 09:16:55 by manaccac         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

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
