/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manaccac <manaccac@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 13:20:57 by manaccac          #+#    #+#             */
/*   Updated: 2020/03/05 14:14:37 by manaccac         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"


void		ft_recover_sprite(t_map *map)
{
	int x;
	int y;
	int i;

	x = 0;
	y = 0;
	i = 0;
	while (x < map->pars.height)
	{
		while (y < map->pars.width)
		{
			if (map->worldmap[x][y] == 2)
				map->nb_sprites++;
			y++;
		}
		x++;
		y = 0;
	}
	if (map->nb_sprites > 50)
	{
		ft_puterror(map, "TO MANY SPRITES");
		return ;
	}

	x = 0;
	y = 0;
	while (x < map->pars.height)
	{
		while (y < map->pars.width)
		{
			if (map->worldmap[x][y] == 2)
			{
				map->sprites[i].posx = x + 0.5;
				map->sprites[i].posy = y + 0.5;
				i++;
			}
			y++;
		}
		x++;
		y = 0;
	}
}

void		ft_check_last_line(t_map *map)
{
	int x;
	int y;

	x = map->pars.height - 1;
	y = 0;
	while (y < map->pars.width)
	{
		if (map->worldmap[x][y] != 1)
		{
			ft_puterror(map, "Error Map\n");
			return ;
		}
		y++;
	}
}

char			*ft_strdup_without_space(char *str)
{
	int		i;
	int		a;
	char	*ret;

	i = 0;
	a = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			a++;
		i++;
	}
	if (!(ret = (char *)malloc(sizeof(char) * (a + 1))))
		return (NULL);
	ret[a] = '\0';
	i = 0;
	a = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			ret[a++] = str[i];
		i++;
	}
	return (ret);
}

int				ft_parsing_choose(t_map *map, char *line)
{
	int choose;

	choose = 0;
	if (map->pars.width != 0)
	{
		choose = 2;
		map->pars.temp = ft_strdup(map->pars.str);
		free(map->pars.str);
		map->pars.str = ft_strjoin(map->pars.temp, line);
		map->pars.twidth = ft_strlen(line);
	}
	if (map->pars.width == 0)
	{
		choose = 1;
		map->pars.str = ft_strdup(line);
		map->pars.width = ft_strlen(line);
		map->pars.twidth = map->pars.width;
	}
	return (choose);
}

int				ft_map_error(char *str, int width)
{
	int i;
	int a;

	i = 0;
	a = 0;
	while (str[i] && i < width)
	{
		if (str[i] != '1')
			return (0);
		i++;
	}
	i = 0;
	while (str[i])
	{
		if (ft_find(str[i], "WESN012") == 0)
			return (0);
		if (str[i] == 'W' || str[i] == 'E' || str[i] == 'S' || str[i] == 'N')
			a++;
		i++;
	}
	if (a != 1)
		return (0);
	return (1);
}

int				ft_parsing_map_two(t_map *map, int i)
{
	if (ft_map_error(map->pars.str, map->pars.width) == 0)
	{
		ft_puterror(map, "Error Map\n");
		return (0);
	}
	map->pars.height = ft_strlen(map->pars.str) / map->pars.width;
	if (!(map->worldmap = (int**)malloc(sizeof(int*) * map->pars.height)))
		return (0);
	while (map->pars.x < map->pars.height)
	{
		if (!(map->worldmap[map->pars.x] =
			(int*)malloc(sizeof(int) * map->pars.width)))
			return (0);
		while (map->pars.y < map->pars.width)
		{
			map->worldmap[map->pars.x][map->pars.y] = map->pars.str[i] - 48;
			i++;
			map->pars.y++;
		}
		map->pars.y = 0;
		map->pars.x++;
	}
	ft_read_map(map);
	ft_check_last_line(map);
	ft_recover_sprite(map);
	return (0);
}

int				ft_parsing_map(t_map *map)
{
	int		fd;
	char	*line;
	int		i;
	int		choose;

	i = 0;
	choose = 0;
	line = NULL;
	fd = open("map.txt", O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		if (map->error == 1)
			return (0);
		if (map->pars.perm != 8)
			ft_parsing(line, map);
		else if (map->pars.perm == 8)
		{
			map->pars.temp = ft_strdup(line);
			free(line);
			line = ft_strdup_without_space(map->pars.temp);
			free(map->pars.temp);
			choose = ft_parsing_choose(map, line);
			free(line);
			if (map->pars.twidth != map->pars.width || line[0] != '1' ||
				line[ft_strlen(line) - 1] != '1')
			{
				ft_putstr_fd("ERROR Map\n", 1);
				map->error = 1;
				return (0);
			}
		}
	}
	return (ft_parsing_map_two(map, i));
}

