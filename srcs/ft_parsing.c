/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manaccac <manaccac@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 07:54:51 by manaccac          #+#    #+#             */
/*   Updated: 2020/03/10 08:13:49 by manaccac         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

int				ft_conv_map(t_map *map)
{
	int x;
	int y;

	x = 0;
	y = 0;
	if (!(map->worldmap = (int**)malloc(sizeof(int*) * map->pars.height)))
		return (0);
	while (map->map_temp[x])
	{
		if (!(map->worldmap[x] = malloc(sizeof(int*) *
				(int)ft_strlen(map->map_temp[x]))))
			return (0);
		while (map->map_temp[x][y])
		{
			map->worldmap[x][y] = ft_atoi_char(map->map_temp[x][y]);
			y++;
		}
		y = 0;
		x++;
	}
	return (0);
}

int				ft_parsing_choose(t_map *map, char *line)
{
	if (map->pars.width != 0)
	{
		map->pars.temp = ft_strdup(map->pars.str);
		free(map->pars.str);
		map->pars.str = ft_strjoin(map->pars.temp, line);
		map->pars.twidth = ft_strlen(line);
	}
	if (map->pars.width == 0)
	{
		map->pars.str = ft_strdup(line);
		map->pars.width = ft_strlen(line);
		map->pars.twidth = map->pars.width;
	}
	return (0);
}

int				ft_parsing_map_three(t_map *map)
{
	int x;

	x = 0;
	ft_check_map_char(map->pars.str);
	map->map_temp = ft_split(map->pars.str, '\n');
	while (map->map_temp[x])
	{
		map->pars.height++;
		x++;
	}
	x = 0;
	if (ft_check_map(map) == 0)
		return (0);
	ft_fill_map(map);
	ft_conv_map(map);
	ft_read_map(map);
	ft_recover_sprite(map);
	return (0);
}

void			ft_parsing_map_two(t_map *map, int count, char *line)
{
	if (line[0] != '1' && count == 1)
		free(line);
	else
	{
		map->pars.temp_two = ft_strdup_pimp(line);
		free(line);
		line = ft_strdup(map->pars.temp_two);
		free(map->pars.temp_two);
		map->pars.temp = ft_strdup(line);
		free(line);
		line = ft_strdup(map->pars.temp);
		free(map->pars.temp);
		ft_parsing_choose(map, line);
		free(line);
	}
}

int				ft_parsing(t_map *map)
{
	int		fd;
	char	*line;
	int		count;

	line = NULL;
	count = 0;
	fd = open(map->cub, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		if (map->error == 1)
			return (0);
		if (map->pars.perm != 8)
			ft_parsing_start(line, map);
		else if (map->pars.perm == 8)
		{
			count++;
			ft_parsing_map_two(map, count, line);
		}
	}
	return (ft_parsing_map_three(map));
}
