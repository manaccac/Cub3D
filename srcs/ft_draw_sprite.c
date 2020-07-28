/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_sprite.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manaccac <manaccac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 09:35:21 by manaccac          #+#    #+#             */
/*   Updated: 2020/07/28 09:14:15 by manaccac         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void	ft_draw_sprite(t_map *map)
{
	t_color		color;
	size_t		d;
	int			y;

	y = map->draw_start.y - 1;
	while (++y < map->draw_end.y)
	{
		d = y * 256 - map->scheight * 128 + map->sprite_height * 128;
		map->tex_y = ((d * map->text_spr.height) / map->sprite_height) / 256;
		color.color = map->text_spr.img_data[map->tex_y *
						map->text_spr.width + map->tex_x];
		if ((color.color & 0xffffff) != 0)
			map->img.data[y * map->scwidth + map->stripe] = color.color;
	}
}
