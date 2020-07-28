/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colision.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manaccac <manaccac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 16:28:24 by manaccac          #+#    #+#             */
/*   Updated: 2020/07/28 09:14:12 by manaccac         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

t_mouvperm		ft_colision(t_map map)
{
	t_mouvperm mouvperm;

	if (map.worldmap[(int)map.player.posX]
		[(int)(map.player.mouveY + map.player.posY)] == 1)
		mouvperm.y = 0;
	else
		mouvperm.y = 1;
	if (map.worldmap[(int)(map.player.mouveX + map.player.posX)]
		[(int)map.player.posY] == 1)
		mouvperm.x = 0;
	else
		mouvperm.x = 1;
	return (mouvperm);
}
