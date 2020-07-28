/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_turnright.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manaccac <manaccac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 09:08:12 by manaccac          #+#    #+#             */
/*   Updated: 2020/07/28 09:14:58 by manaccac         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

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
