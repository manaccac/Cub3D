/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_parsing.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: manaccac <manaccac@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/25 07:54:51 by manaccac     #+#   ##    ##    #+#       */
/*   Updated: 2020/02/25 09:12:25 by manaccac    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/cube.h"

void			ft_init_map_two(t_map *map, int in_char)
{
	if (in_char == 'S')
	{
		map->player.dirX = 1;
		map->player.dirY = 0;
		map->player.planeX = 0;
		map->player.planeY = -0.66;
	}
	else if (in_char == 'N')
	{
		map->player.dirX = -1;
		map->player.dirY = 0;
		map->player.planeX = 0;
		map->player.planeY = 0.66;
	}
}

void			ft_init_map(t_map *map, int in_char)
{
	if (in_char == 'E')
	{
		map->player.dirX = 0;
		map->player.dirY = 1;
		map->player.planeX = 0.66;
		map->player.planeY = 0;
	}
	else if (in_char == 'W')
	{
		map->player.dirX = 0;
		map->player.dirY = -1;
		map->player.planeX = -0.66;
		map->player.planeY = 0;
	}
}

int				ft_read_map(t_map *map)
{
	int			x;
	int			y;
	int			in_char;

	x = 0;
	y = 0;
	while (x < map->pars.height)
	{
		while (y < map->pars.width)
		{
			if (map->worldmap[x][y] + 48 >= 'E')
			{
				in_char = map->worldmap[x][y] + 48;
				ft_init_map(map, in_char);
				ft_init_map_two(map, in_char);
				map->worldmap[x][y] = 0;
				map->player.posX = x + 0.5;
				map->player.posY = y + 0.5;
			}
			y++;
		}
		y = 0;
		x++;
	}
	return (0);
}

int				ft_find(const char c, const char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}
/*
int				ft_ground_sky(char *str, int i, t_map *map)
{
	if (str[i] == ',')
		i++;
	if (str[0] == 'F')
		map->pars.ground_b = ft_atoi_pimp(str, i);
	if (str[0] == 'C')
		map->pars.sky_b = ft_atoi_pimp(str, i);
	while ((ft_isdigit(str[i]) == 1) && str[i] != '\0')
	{
		i++;
		if (str[i] == '\0')
		{
			free(str);
			map->pars.perm++;
			return (0);
		}
	}
	ft_putstr("Couleur sol/plafond Error.\n");
	free(str);
	return (0);
}
*/
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
		{
			return (0);
		}
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
		ft_putstr_fd("Error map.", 1);
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
			map->pars.temp = ft_strdup(line);
			free(line);
			line = ft_strdup_without_space(map->pars.temp);
			free(map->pars.temp);
			choose = ft_parsing_choose(map, line);
			free(line);
			if (map->pars.twidth != map->pars.width || line[0] != '1' ||
				line[ft_strlen(line) - 1] != '1')
			{
				ft_putstr_fd("Error map.\n", 1);
				return (0);
			}
	}
	return (ft_parsing_map_two(map, i));
}
