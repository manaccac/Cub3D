/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ifray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manaccac <manaccac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 09:29:29 by manaccac          #+#    #+#             */
/*   Updated: 2020/07/28 09:14:32 by manaccac         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void	ft_ifray(t_player *player, t_calray *calray)
{
	if (calray->rayDirX < 0)
	{
		calray->stepX = -1;
		calray->sideDistX = (player->posX - calray->mapX) * calray->deltaDistX;
	}
	else
	{
		calray->stepX = 1;
		calray->sideDistX = (calray->mapX + 1.0 - player->posX) *
			calray->deltaDistX;
	}
	if (calray->rayDirY < 0)
	{
		calray->stepY = -1;
		calray->sideDistY = (player->posY - calray->mapY) *
			calray->deltaDistY;
	}
	else
	{
		calray->stepY = 1;
		calray->sideDistY = (calray->mapY + 1.0 - player->posY) *
			calray->deltaDistY;
	}
}
