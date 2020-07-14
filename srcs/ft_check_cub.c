/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_cub.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manaccac <manaccac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 08:00:30 by manaccac          #+#    #+#             */
/*   Updated: 2020/07/14 11:22:55 by manaccac         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

int		ft_check_cub(char *str)
{
	int i;

	i = 0;
	while (str[i] != '.')
		i++;
	if (str[i] != '.')
		return (0);
	i++;
	if (str[i] == 'c' && str[i + 1] == 'u' && str[i + 2] == 'b'
		&& str[i + 3] == '\0')
		return (1);
	return (0);
}
