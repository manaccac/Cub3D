/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprite_raycasting.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manaccac <manaccac@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 11:48:08 by manaccac          #+#    #+#             */
/*   Updated: 2020/03/05 13:46:29 by manaccac         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

int				ft_abs1(int nb)
{
	return (nb < 0 ? -nb : nb);
}

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
		color.color = map->text_spr.img_data[map->tex_y * map->text_spr.width + map->tex_x];
		if ((color.color & 0xffffff) != 0)
			map->img.data[y * map->scwidth + map->stripe] = color.color;
	}
}

void		ft_sort(t_map *map)
{
	int i;

	i = 0;
	while (i < map->nb_sprites)
	{
		map->sprites[i].dist = ((map->player.posX - map->sprites[i].posx)
		* (map->player.posX - map->sprites[i].posx) +
		(map->player.posY - map->sprites[i].posy) * (map->player.posY - map->sprites[i].posy));
		i++;
	}
	int j = 0;
	double swapx = 0.0;
	double swapy = 0.0;
	double dist = 0.0;
	i = 1;
	while (j < map->nb_sprites)
	{
		while (i < map->nb_sprites)
		{
			if (map->sprites[j].dist < map->sprites[i].dist)
			{
				swapx = map->sprites[i].posx;
				swapy = map->sprites[i].posy;
				dist = map->sprites[i].dist;
				map->sprites[i] = map->sprites[j];
				map->sprites[j].posx = swapx;
				map->sprites[j].posy = swapy;
				map->sprites[j].dist = dist;
			}
			i++;
		}
		j++;
		i = j + 1;
	}
}

void	ft_raycasting_sprite(t_map *map)
{
	int i;

	i = 0;
	ft_sort(map);
  	while (i < map->nb_sprites)
	{
		map->sprite.x = map->sprites[i].posx - map->player.posX;
		map->sprite.y = map->sprites[i].posy - map->player.posY;
		map->inv_det = 1.0 / ((map->player.planeX * map->player.dirY) - (map->player.dirX * map->player.planeY));
		map->transform.x = map->inv_det * ((map->player.dirY * map->sprite.x) - (map->player.dirX * map->sprite.y));
		map->transform.y = map->inv_det * ((-map->player.planeY * map->sprite.x) + (map->player.planeX * map->sprite.y));
		map->sprite_screen_x = (int)(map->scwidth / 2) * (1 + map->transform.x / map->transform.y);
		map->sprite_height = abs((int)(map->scheight / (map->transform.y)));
		map->draw_start.y = (-map->sprite_height / 2 + map->scheight / 2);
		if (map->draw_start.y < 0)
			map->draw_start.y = 0;
		map->draw_end.y = (map->sprite_height / 2 + map->scheight / 2);
		if (map->draw_end.y >= map->scheight)
			map->draw_end.y = map->scheight - 1;
		map->sprite_width = abs((int)(map->scheight / (map->transform.y)));
		map->draw_start.x = -map->sprite_width / 2 + map->sprite_screen_x;
		if (map->draw_start.x < 0)
			map->draw_start.x = 0;
		map->draw_end.x = map->sprite_width / 2 + map->sprite_screen_x;
		if (map->draw_end.x >= map->scwidth)
			map->draw_end.x = map->scwidth - 1;
		map->stripe = map->draw_start.x;

		while (map->stripe < map->draw_end.x)
		{
			map->tex_x = (int)((256 * (map->stripe -  (-map->sprite_width / 2 + map->sprite_screen_x)) * map->text_spr.width / map->sprite_width) / 256);
			if (map->transform.y > 0 && map->stripe > 0 && map->stripe < map->scwidth && map->transform.y < map->zbuffer[map->stripe])
				ft_draw_sprite(map);
			map->stripe++;
		}
		i++;
	}
}
