/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_for.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manaccac <manaccac@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 12:54:24 by manaccac          #+#    #+#             */
/*   Updated: 2020/03/09 12:56:22 by manaccac         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

int				ft_fill_map_two(t_map *map, int x, int y)
{
	while (map->map_temp[x])
	{
		if (map->map_temp[x][y] == ' ')
			map->map_temp[x][y] = '1';
		if (map->map_temp[x][(int)ft_strlen(map->map_temp[x]) - 1] == ' ')
			map->map_temp[x][(int)ft_strlen(map->map_temp[x]) - 1] = '1';
		x++;
	}
	x = 0;
	y = 0;
	while (map->map_temp[x])
	{
		while (map->map_temp[x][y])
		{
			if (map->map_temp[x][y] == ' ')
				map->map_temp[x][y] = '0';
			y++;
		}
		y = 0;
		x++;
	}
	return (1);
}

int				ft_fill_map(t_map *map)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (map->map_temp[x][y])
	{
		if (map->map_temp[x][y] == ' ')
			map->map_temp[x][y] = '1';
		y++;
	}
	x = map->pars.height - 1;
	y = 0;
	while (map->map_temp[x][y])
	{
		if (map->map_temp[x][y] == ' ')
			map->map_temp[x][y] = '1';
		y++;
	}
	x = 0;
	y = 0;
	return (ft_fill_map_two(map, x, y));
}

void			ft_recover_sprite(t_map *map)
{
	int x;
	int y;
	int i;

	x = 0;
	y = 0;
	i = 0;
	while (x < map->pars.height)
	{
		while (y < (int)ft_strlen(map->map_temp[x]))
		{
			if (map->worldmap[x][y] == 2)
				map->nb_sprites++;
			y++;
		}
		x++;
		y = 0;
	}
	ft_recover_sprite_two(map, x, y, i);
}

void			ft_recover_sprite_two(t_map *map, int x, int y, int i)
{
	if (!(map->sprites = malloc(sizeof(int *) * map->nb_sprites)))
		return ;
	x = 0;
	y = 0;
	while (x < map->pars.height)
	{
		while (y < (int)ft_strlen(map->map_temp[x]))
		{
			if (map->worldmap[x][y] == 2 && i < map->nb_sprites)
			{
				map->sprites[i].posx = x;
				map->sprites[i].posy = y;
				i++;
			}
			y++;
		}
		x++;
		y = 0;
	}
}
