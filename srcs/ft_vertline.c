/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vertline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manaccac <manaccac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 09:12:31 by manaccac          #+#    #+#             */
/*   Updated: 2020/07/28 09:15:02 by manaccac         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void		ft_vertline(int h, int x, t_map map)
{
	int				y;
	int				notwall;
	int				it;

	y = -1;
	if (h == -1)
		return ;
	notwall = (map.scheight - h) / 2;
	map = ft_if_verline(map);
	while (++y < map.scheight)
	{
		if (y <= notwall)
			map.img.data[x + y * map.scwidth] = 0x2880BB;
		else if (y < (map.scheight - notwall) && y > notwall)
		{
			map.texty = ((double)y - (double)notwall) /
				(double)(map.scheight - notwall - notwall) * 64;
			it = (int)(map.texty) * map.texture[map.wall_text].sizeline /
				4 + (int)(map.textx);
			map.img.data[y * map.scwidth + x] =
				map.texture[map.wall_text].data[it];
		}
		else
			map.img.data[x + y * map.scwidth] = 0x585551;
	}
}
