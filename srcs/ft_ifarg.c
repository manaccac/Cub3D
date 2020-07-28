/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ifarg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manaccac <manaccac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 16:22:42 by manaccac          #+#    #+#             */
/*   Updated: 2020/07/28 09:14:24 by manaccac         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

t_map		ft_ifarg(int argc, char **argv, t_map map)
{
	if (argc >= 2)
	{
		if (ft_check_cub(argv[1]) == 0)
		{
			ft_putstr_v("Need .cub");
		}
		else
			map.cub = ft_strdup(argv[1]);
	}
	return (map);
}
