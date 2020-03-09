/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manaccac <manaccac@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 14:01:39 by manaccac          #+#    #+#             */
/*   Updated: 2020/03/09 13:59:44 by manaccac         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

int				ft_check_colors(t_map *map, int colors)
{
	if (colors > 255)
	{
		colors = 255;
		map->error_parsing = 1;
		return (colors);
	}
	if (colors < 0)
	{
		colors = 0;
		map->error_parsing = 1;
		return (colors);
	}
	return (colors);
}

int				ft_check_parsing(t_map *map)
{
	map->pars.ground_r = ft_check_colors(map, map->pars.ground_r);
	map->pars.ground_g = ft_check_colors(map, map->pars.ground_g);
	map->pars.ground_b = ft_check_colors(map, map->pars.ground_b);
	if (map->error_parsing == 1)
		ft_putstr_v("Color ground automatically set to 0/255\n");
	map->error_parsing = 0;
	map->pars.sky_r = ft_check_colors(map, map->pars.sky_r);
	map->pars.sky_g = ft_check_colors(map, map->pars.sky_g);
	map->pars.sky_b = ft_check_colors(map, map->pars.sky_b);
	if (map->error_parsing == 1)
		ft_putstr_v("Color sky automatically set to 0/255\n");
	if (map->scwidth > 2560)
	{
		map->scwidth = 2560;
		ft_putstr_v("ScreenWidth automatically set to 2560\n");
	}
	if (map->scheight > 1440)
	{
		map->scheight = 1440;
		ft_putstr_v("ScreenHeight automatically set to 1440\n");
	}
	return (0);
}

int				ft_check_map(t_map *map)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (map->map_temp[x])
	{
		while (map->map_temp[x][y])
		{
			if (map->map_temp[x][y] == '0')
			{
				if (ft_check_wall(x, y, map) == -1)
				{
					ft_puterror(map, "Error map\n");
					return (0);
				}
			}
			y++;
		}
		y = 0;
		x++;
	}
	return (1);
}

int				ft_check_map_char(char *str)
{
	int i;
	int a;

	i = 0;
	a = 0;
	while (str[i])
	{
		if (ft_find(str[i], "WESN012") == 0)
			return (0);
		if (str[i] == 'W' || str[i] == 'E' || str[i] == 'S' || str[i] == 'N')
			a++;
		i++;
	}
	if (a != 1)
		return (0);
	return (1);
}

int				ft_check_wall(int x, int y, t_map *map)
{
	map->a = y;
	while (map->map_temp[x][map->a] != '1' && map->a > 0
			&& map->map_temp[x][map->a] != ' ')
		map->a--;
	if (map->map_temp[x][map->a] != '1')
		return (-1);
	map->a = y;
	while (map->map_temp[x][map->a] && map->map_temp[x][map->a] != '1'
			&& map->map_temp[x][map->a] != ' ')
		map->a++;
	if (map->map_temp[x][map->a] != '1')
		return (-1);
	map->b = x;
	while (map->map_temp[map->b][y] != '1' && map->b > 0
			&& map->map_temp[map->b][y] != ' ')
		map->b--;
	if (map->map_temp[map->b][y] != '1')
		return (-1);
	map->b = x;
	while (map->b < map->pars.height - 1 && map->map_temp[map->b][y] != '1'
			&& map->map_temp[map->b][y] != ' ')
		map->b++;
	if (map->map_temp[map->b][y] != '1')
		return (-1);
	return (1);
}
