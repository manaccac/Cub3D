/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_if_verline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manaccac <manaccac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 09:11:30 by manaccac          #+#    #+#             */
/*   Updated: 2020/07/28 09:14:20 by manaccac         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

t_map		ft_if_verline(t_map map)
{
	if (map.wall_dir == 'W' || map.wall_dir == 'E')
		map.textx = (map.hit_wall_x - (int)map.hit_wall_x) * 64;
	else if (map.wall_dir == 'N' || map.wall_dir == 'S')
		map.textx = (map.hit_wall_y - (int)map.hit_wall_y) * 64;
	return (map);
}
