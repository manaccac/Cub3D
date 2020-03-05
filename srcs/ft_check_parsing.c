/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manaccac <manaccac@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 14:01:39 by manaccac          #+#    #+#             */
/*   Updated: 2020/03/05 14:10:14 by manaccac         ###   ########lyon.fr   */
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
		ft_putstr("Color ground automatically set to 0/255\n");
	map->error_parsing = 0;
	map->pars.sky_r = ft_check_colors(map, map->pars.sky_r);
	map->pars.sky_g = ft_check_colors(map, map->pars.sky_g);
	map->pars.sky_b = ft_check_colors(map, map->pars.sky_b);
	if (map->error_parsing == 1)
		ft_putstr("Color sky automatically set to 0/255\n");
	if (map->scwidth > 2560)
	{
		map->scwidth = 2560;
		ft_putstr("ScreenWidth automatically set to 2560\n");
	}
	if (map->scheight > 1440)
	{
		map->scheight = 1440;
		ft_putstr("ScreenHeight automatically set to 1440\n");
	}
	return (0);
}
