/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapcreate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manaccac <manaccac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 16:24:14 by manaccac          #+#    #+#             */
/*   Updated: 2020/07/28 09:15:58 by manaccac         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

t_map		ft_mapcreate(t_map map)
{
	map.zbuffer = (double *)malloc(sizeof(double) * map.scwidth);
	map.mlx_ptr = mlx_init();
	map = ft_texture(map);
	map.img_ptr = mlx_new_image(map.mlx_ptr, map.scwidth, map.scheight);
	map.img.data = (int*)mlx_get_data_addr(map.img_ptr,
		&map.img.bpp, &map.img.sizeline, &map.img.endian);
	map.win_ptr = mlx_new_window(map.mlx_ptr, map.scwidth,
		map.scheight, "CUBE");
	return (map);
}
