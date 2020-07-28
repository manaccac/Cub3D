/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printwall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manaccac <manaccac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 09:14:42 by manaccac          #+#    #+#             */
/*   Updated: 2020/07/28 10:29:44 by manaccac         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

int			ft_printwall(t_map map)
{
	double	ray_dist;
	int		h;
	int		x;

	x = 0;
	while (x < map.scwidth)
	{
		map.img.img_color = mlx_get_color_value(map.mlx_ptr, 0xffffff);
		ray_dist = raycasting(map.player, x, &map);
		h = (int)(map.scheight / ray_dist);
		ft_vertline(h, x, map);
		map.zbuffer[x] = ray_dist;
		x++;
	}
	ft_raycasting_sprite(&map);
	mlx_put_image_to_window(map.mlx_ptr, map.win_ptr, map.img_ptr, 0, 0);
	return (1);
}
