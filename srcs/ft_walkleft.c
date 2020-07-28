/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_walkleft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manaccac <manaccac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 09:03:38 by manaccac          #+#    #+#             */
/*   Updated: 2020/07/28 09:15:11 by manaccac         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

int			ft_walkleft(t_map *map)
{
	map->player.mouveX -= map->player.planeX * 0.15 * map->player.movea;
	map->player.mouveY -= map->player.planeY * 0.15 * map->player.movea;
	return (0);
}
