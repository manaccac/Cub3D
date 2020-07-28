/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_walkright.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manaccac <manaccac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 09:05:39 by manaccac          #+#    #+#             */
/*   Updated: 2020/07/28 09:15:14 by manaccac         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

int			ft_walkright(t_map *map)
{
	map->player.mouveX += map->player.planeX * 0.15 * map->player.moved;
	map->player.mouveY += map->player.planeY * 0.15 * map->player.moved;
	return (0);
}
