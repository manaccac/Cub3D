/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wall_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manaccac <manaccac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 09:31:13 by manaccac          #+#    #+#             */
/*   Updated: 2020/07/28 09:15:17 by manaccac         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

char	ft_wall_dir(t_calray calray)
{
	if (calray.side == 1)
	{
		if (calray.stepY > 0)
			return ('W');
		else
			return ('E');
	}
	if (calray.side == 0)
	{
		if (calray.stepX > 0)
			return ('S');
		else
			return ('N');
	}
	return (0);
}
