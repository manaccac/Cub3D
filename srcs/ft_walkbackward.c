/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_walkbackward.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manaccac <manaccac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 16:32:53 by manaccac          #+#    #+#             */
/*   Updated: 2020/07/28 09:15:05 by manaccac         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

int			ft_walkbackward(t_map *map)
{
	map->player.mouveX -= map->player.dirX * 0.15 * map->player.moves;
	map->player.mouveY -= map->player.dirY * 0.15 * map->player.moves;
	return (0);
}
