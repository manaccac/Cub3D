/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_texture.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manaccac <manaccac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 16:27:33 by manaccac          #+#    #+#             */
/*   Updated: 2020/07/28 09:14:51 by manaccac         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

t_map		ft_texture(t_map map)
{
	int	i;

	i = 0;
	while (i != 4)
	{
		map.texture[i].image = mlx_xpm_file_to_image(map.mlx_ptr,
			map.texture[i].textpath, &map.texture[i].width,
			&map.texture[i].height);
		map.texture[i].data = (int*)mlx_get_data_addr(map.texture[i].image
			, &map.texture[i].bpp,
			&map.texture[i].sizeline, &map.texture[i].endian);
		i++;
	}
	map.text_spr.image = mlx_xpm_file_to_image(map.mlx_ptr,
		map.text_spr.textpath, &map.text_spr.width, &map.text_spr.height);
	map.text_spr.img_data = (int*)mlx_get_data_addr(map.text_spr.image,
		&map.text_spr.bpp, &map.text_spr.sizeline, &map.text_spr.endian);
	return (map);
}
