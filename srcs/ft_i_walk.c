/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_i_walk.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manaccac <manaccac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 09:16:11 by manaccac          #+#    #+#             */
/*   Updated: 2020/07/28 09:14:18 by manaccac         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

int			ft_i_walk(t_map *map)
{
	mlx_clear_window(map->mlx_ptr, map->win_ptr);
	map->player.mouveX = 0;
	map->player.mouveY = 0;
	if (map->player.movew)
		ft_walkforward(map);
	if (map->player.moved)
		ft_walkright(map);
	if (map->player.moves)
		ft_walkbackward(map);
	if (map->player.movea)
		ft_walkleft(map);
	if (map->player.key_e)
		ft_turnright(map);
	if (map->player.key_q)
		ft_turnleft(map);
	map->mouvperm = ft_colision(*map);
	if (map->mouvperm.x)
		map->player.posX = map->player.posX + map->player.mouveX;
	if (map->mouvperm.y)
		map->player.posY = map->player.posY + map->player.mouveY;
	ft_printwall(*map);
	return (0);
}
