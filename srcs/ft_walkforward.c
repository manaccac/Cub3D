/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_walkforward.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manaccac <manaccac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 16:31:58 by manaccac          #+#    #+#             */
/*   Updated: 2020/07/28 09:15:07 by manaccac         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

int			ft_walkforward(t_map *map)
{
	map->player.mouveX += map->player.dirX * 0.15 * map->player.movew;
	map->player.mouveY += map->player.dirY * 0.15 * map->player.movew;
	return (0);
}
