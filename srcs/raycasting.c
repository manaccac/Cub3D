/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manaccac <manaccac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 08:38:04 by manaccac          #+#    #+#             */
/*   Updated: 2020/07/19 09:31:23 by manaccac         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

double	ft_abs(double n)
{
	if (n >= 0)
		return (n);
	return (-n);
}

void	ft_inite_ray(t_player *player, t_calray *calray, int x, t_map *map)
{
	player->cameraX = 2 * x / (double)map->scwidth - 1;
	calray->rayDirX = player->dirX + player->planeX * player->cameraX;
	calray->rayDirY = player->dirY + player->planeY * player->cameraX;
	calray->mapX = (int)player->posX;
	calray->mapY = (int)player->posY;
	calray->deltaDistX = ft_abs(1 / calray->rayDirX);
	calray->deltaDistY = ft_abs(1 / calray->rayDirY);
	calray->side = 0;
	calray->hit = 0;
}

void	ft_ifray2(t_calray *calray, t_map *map)
{
	if (calray->sideDistX < calray->sideDistY)
	{
		calray->sideDistX += calray->deltaDistX;
		calray->mapX += calray->stepX;
		calray->side = 0;
	}
	else
	{
		calray->sideDistY += calray->deltaDistY;
		calray->mapY += calray->stepY;
		calray->side = 1;
	}
	if (map->worldmap[calray->mapX][calray->mapY] == 1)
		calray->hit = 1;
}

void	ft_pole(t_map *map)
{
	if (map->wall_dir == 'W')
		map->wall_text = 0;
	else if (map->wall_dir == 'E')
		map->wall_text = 1;
	else if (map->wall_dir == 'N')
		map->wall_text = 2;
	else if (map->wall_dir == 'S')
		map->wall_text = 3;
}

double	raycasting(t_player player, int x, t_map *map)
{
	t_calray calray;

	ft_inite_ray(&player, &calray, x, map);
	ft_ifray(&player, &calray);
	while (calray.hit == 0)
		ft_ifray2(&calray, map);
	if (calray.side == 0)
		calray.perpWallDist = (calray.mapX - player.posX +
			(1 - calray.stepX) / 2) / calray.rayDirX;
	else
		calray.perpWallDist = (calray.mapY - player.posY +
			(1 - calray.stepY) / 2) / calray.rayDirY;
	map->hit_wall_x = player.posX + calray.rayDirX *
		calray.perpWallDist;
	map->hit_wall_y = player.posY + calray.rayDirY *
		calray.perpWallDist;
	map->wall_dir = ft_wall_dir(calray);
	ft_pole(map);
	return (calray.perpWallDist);
}
