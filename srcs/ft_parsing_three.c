/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_three.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manaccac <manaccac@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 13:27:59 by manaccac          #+#    #+#             */
/*   Updated: 2020/03/02 08:17:18 by manaccac         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void			ft_init_map_two(t_map *map, int in_char)
{
	if (in_char == 'S')
	{
		map->player.dirX = 1;
		map->player.dirY = 0;
		map->player.planeX = 0;
		map->player.planeY = -0.66;
	}
	else if (in_char == 'N')
	{
		map->player.dirX = -1;
		map->player.dirY = 0;
		map->player.planeX = 0;
		map->player.planeY = 0.66;
	}
}

void			ft_init_map(t_map *map, int in_char)
{
	if (in_char == 'E')
	{
		map->player.dirX = 0;
		map->player.dirY = 1;
		map->player.planeX = 0.66;
		map->player.planeY = 0;
	}
	else if (in_char == 'W')
	{
		map->player.dirX = 0;
		map->player.dirY = -1;
		map->player.planeX = -0.66;
		map->player.planeY = 0;
	}
}

int				ft_read_map(t_map *map)
{
	int			x;
	int			y;
	int			in_char;

	x = 0;
	y = 0;
	while (x < map->pars.height)
	{
		while (y < map->pars.width)
		{
			if (map->worldmap[x][y] + 48 >= 'E')
			{
				in_char = map->worldmap[x][y] + 48;
				ft_init_map(map, in_char);
				ft_init_map_two(map, in_char);
				map->worldmap[x][y] = 0;
				map->player.posX = x + 0.5;
				map->player.posY = y + 0.5;
			}
			y++;
		}
		y = 0;
		x++;
	}
	return (0);
}

int				ft_find(const char c, const char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}

int				ft_ground_sky(char *str, int i, t_map *map)
{
	if (str[i] == ',')
		i++;
	if (str[0] == 'F')
		map->pars.ground_b = ft_atoi_pimp(str, i);
	if (str[0] == 'C')
		map->pars.sky_b = ft_atoi_pimp(str, i);
	while ((ft_isdigit(str[i]) == 1) && str[i] != '\0')
	{
		i++;
		if (str[i] == '\0')
		{
			free(str);
			map->pars.perm++;
			return (0);
		}
	}
	ft_puterror(map);
	free(str);
	return (0);
}
