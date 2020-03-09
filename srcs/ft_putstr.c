/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manaccac <manaccac@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 13:26:47 by manaccac          #+#    #+#             */
/*   Updated: 2020/03/09 13:34:23 by manaccac         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"
#include <unistd.h>

void	ft_putstr_v(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		ft_putchar_v(str[i]);
		i++;
	}
}
