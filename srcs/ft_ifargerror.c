/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ifargerror.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manaccac <manaccac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 16:18:22 by manaccac          #+#    #+#             */
/*   Updated: 2020/07/28 09:14:28 by manaccac         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

int		ft_ifargerror(int argc, char **argv, t_map map)
{
	if (argc >= 2)
	{
		if (ft_check_cub(argv[1]) == 0)
		{
			ft_putstr_v("Need .cub");
			return (0);
		}
	}
	if (argc > 3)
	{
		ft_putstr_v("To many arguments");
		return (0);
	}
	return (1);
}
