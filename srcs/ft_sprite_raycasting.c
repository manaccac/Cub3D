/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprite_raycasting.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manaccac <manaccac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 11:48:08 by manaccac          #+#    #+#             */
/*   Updated: 2020/07/28 10:36:56 by manaccac         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

int		ft_abs1(int nb)
{
	return (nb < 0 ? -nb : nb);
}

int		ft_if_nbsprt(t_map *map, int i, double dist)
{
	if (map->sprites[map->sprt.j].dist < map->sprites[i].dist)
	{
		map->sprt.swapx = map->sprites[i].posx;
		map->sprt.swapy = map->sprites[i].posy;
		dist = map->sprites[i].dist;
		map->sprites[i] = map->sprites[map->sprt.j];
		map->sprites[map->sprt.j].posx = map->sprt.swapx;
		map->sprites[map->sprt.j].posy = map->sprt.swapy;
		map->sprites[map->sprt.j].dist = dist;
	}
	return (i);
}

void	ft_sort(t_map *map)
{
	int		i;
	double	dist;

	map->sprt.j = 0;
	map->sprt.swapx = 0.0;
	map->sprt.swapy = 0.0;
	dist = 0.0;
	i = 0;
	while (i < map->nb_sprites)
	{
		map->sprites[i].dist = ((map->player.posX - map->sprites[i].posx)
		* (map->player.posX - map->sprites[i].posx) +
		(map->player.posY - map->sprites[i].posy) *
			(map->player.posY - map->sprites[i].posy));
		i++;
	}
	i = 1;
	while (map->sprt.j < map->nb_sprites)
	{
		while (i < map->nb_sprites)
			i = ft_if_nbsprt(map, i, dist) + 1;
		map->sprt.j++;
		i = map->sprt.j + 1;
	}
}

void	ft_if_sprtray(t_map *map, int i)
{
	map->sprite.x = map->sprites[i].posx - map->player.posX;
	map->sprite.y = map->sprites[i].posy - map->player.posY;
	map->inv_det = 1.0 / ((map->player.planeX * map->player.dirY) -
		(map->player.dirX * map->player.planeY));
	map->transform.x = map->inv_det * ((map->player.dirY * map->sprite.x) -
		(map->player.dirX * map->sprite.y));
	map->transform.y = map->inv_det * ((-map->player.planeY * map->sprite.x)
		+ (map->player.planeX * map->sprite.y));
	map->sprite_screen_x = (int)(map->scwidth / 2) *
		(1 + map->transform.x / map->transform.y);
	map->sprite_height = abs((int)(map->scheight / (map->transform.y)));
	map->draw_start.y = (-map->sprite_height / 2 + map->scheight / 2);
	if (map->draw_start.y < 0)
		map->draw_start.y = 0;
	map->draw_end.y = (map->sprite_height / 2 + map->scheight / 2);
	if (map->draw_end.y >= map->scheight)
		map->draw_end.y = map->scheight - 1;
	map->sprite_width = abs((int)(map->scheight / (map->transform.y)));
	map->draw_start.x = -map->sprite_width / 2 + map->sprite_screen_x;
}

void	ft_raycasting_sprite(t_map *map)
{
	int i;

	i = 0;
	ft_sort(map);
	while (i < map->nb_sprites)
	{
		ft_if_sprtray(map, i);
		if (map->draw_start.x < 0)
			map->draw_start.x = 0;
		map->draw_end.x = map->sprite_width / 2 + map->sprite_screen_x;
		if (map->draw_end.x >= map->scwidth)
			map->draw_end.x = map->scwidth - 1;
		map->stripe = map->draw_start.x;
		while (map->stripe < map->draw_end.x)
		{
			map->tex_x = (int)((256 * (map->stripe - (-map->sprite_width / 2 +
				map->sprite_screen_x)) *
				map->text_spr.width / map->sprite_width) / 256);
			if (map->transform.y > 0 && map->stripe > 0 && map->stripe <
				map->scwidth && map->transform.y < map->zbuffer[map->stripe])
				ft_draw_sprite(map);
			map->stripe++;
		}
		i++;
	}
}
