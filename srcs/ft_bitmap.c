/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bitmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manaccac <manaccac@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 08:55:56 by manaccac          #+#    #+#             */
/*   Updated: 2020/03/10 11:56:49 by manaccac         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void	bitmap_image(t_map *map, int fd, t_bih bih)
{
	int				x;
	int				y;
	int				ble;
	unsigned char	color[3];
	y = map->scheight - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < map->scwidth)
		{
			ble = map->img.data[x + y * map->scwidth];
			color[0] = ble % 256;
			ble /= 256;
			color[1] = ble % 256;
			ble /= 256;
			color[2] = ble % 256;
			write(fd, &color, sizeof(color));
			x++;
		}
		y--;
	}
}

void	save_bitmap(const char *filename, t_map *map)
{
	int			fd;
	t_bfh		bfh;
	t_bih		bih;
	ft_memcpy(&bfh.bitmap_type, "BM", 2);
	bfh.file_size = map->scwidth * map->scheight * 4 + 54;
	bfh.reserved1 = 0;
	bfh.reserved2 = 0;
	bfh.offset_bits = 0;
	bih.size_header = sizeof(bih);
	bih.width = map->scwidth;
	bih.height = map->scheight;
	bih.planes = 1;
	bih.bit_count = 24;
	bih.compression = 0;
	bih.image_size = map->scwidth * map->scheight * 4 + 54;
	bih.ppm_x = 2;
	bih.ppm_y = 2;
	bih.clr_used = 0;
	bih.clr_important = 0;
	fd = open(filename, O_RDWR | O_CREAT, 0777);
	write(fd, &bfh, 14);
	write(fd, &bih, sizeof(bih));
	bitmap_image(map, fd, bih);
	close(fd);
}
