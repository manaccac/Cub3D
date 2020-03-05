/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manaccac <manaccac@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 07:54:51 by manaccac          #+#    #+#             */
/*   Updated: 2020/03/05 08:17:09 by manaccac         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

char			*ft_parsing_texture(char *s, t_map *map)
{
	int		i;
	char	*str;
	char	*dest;

	i = 1;
	str = ft_strdup(s);
	while (str[i] != ' ')
		i++;
	i++;
	dest = ft_strcpy_pimp(dest, str, i);
	while (str[i] != '\0' && ft_isascii(str[i]) == 1)
		i++;
	if (str[i] == '\0')
	{
		free(str);
		map->pars.perm++;
		return (dest);
	}
	ft_puterror(map);
	free(str);
	return (dest);
}

int				ft_resolution_two(char *str, t_map *map, int i, int j)
{
	while ((ft_isdigit(str[i]) == 1) && str[i] != ' ')
	{
		map->pars.height_str[j] = str[i];
		i++;
		j++;
		if (str[i] == '\0')
		{
			map->scwidth = ft_atoi(map->pars.width_str);
			map->scheight = ft_atoi(map->pars.height_str);
			free(str);
			free(map->pars.width_str);
			free(map->pars.height_str);
			map->pars.perm++;
			return (0);
		}
	}
	ft_puterror(map);
	free(map->pars.width_str);
	free(map->pars.height_str);
	free(str);
	return (0);
}

int				ft_parsing_resolution(char *s, t_map *map)
{
	int		i;
	int		j;
	char	*str;

	i = 1;
	j = 0;
	if (!(map->pars.width_str = (char *)malloc(sizeof(char) * 4)))
		return (0);
	if (!(map->pars.height_str = (char *)malloc(sizeof(char) * 4)))
		return (0);
	str = ft_strdup(s);
	while (str[i] == ' ')
		i++;
	while ((ft_isdigit(str[i]) == 1) && str[i] != ' ')
	{
		map->pars.width_str[j] = str[i];
		i++;
		j++;
	}
	j = 0;
	while (str[i] == ' ')
		i++;
	return (ft_resolution_two(str, map, i, j));
}

int				ft_parsing_ground_sky(char *s, t_map *map)
{
	int		i;
	char	*str;

	i = 1;
	str = ft_strdup(s);
	while (str[i] == ' ' && str[i])
		i++;
	if (str[0] == 'F')
		map->pars.ground_r = ft_atoi_pimp(str, i);
	if (str[0] == 'C')
		map->pars.sky_r = ft_atoi_pimp(str, i);
	while ((ft_isdigit(str[i]) == 1) && str[i] != ',' && str[i])
		i++;
	if (str[i] == ',')
		i++;
	if (str[0] == 'F')
		map->pars.ground_g = ft_atoi_pimp(str, i);
	if (str[0] == 'C')
		map->pars.sky_g = ft_atoi_pimp(str, i);
	while ((ft_isdigit(str[i]) == 1) && str[i] != ',' && str[i])
		i++;
	return (ft_ground_sky(str, i, map));
}

int				ft_parsing(char *s, t_map *map)
{
	if (ft_strncmp(s, "R ", 2) == 0)
		return (ft_parsing_resolution(s, map));
	else if (ft_strncmp(s, "F ", 2) == 0 || ft_strncmp(s, "C ", 2) == 0)
		return (ft_parsing_ground_sky(s, map));
	else if (ft_strncmp(s, "NO ", 2) == 0)
		map->texture[0].textpath = ft_parsing_texture(s, map);
	else if (ft_strncmp(s, "SO ", 2) == 0)
		map->texture[1].textpath = ft_parsing_texture(s, map);
	else if (ft_strncmp(s, "EA ", 2) == 0)
		map->texture[2].textpath = ft_parsing_texture(s, map);
	else if (ft_strncmp(s, "WE ", 2) == 0)
		map->texture[3].textpath = ft_parsing_texture(s, map);
	else if (ft_strncmp(s, "S ", 1) == 0)
		map->text_spr.textpath = ft_parsing_texture(s, map);

/*
	dprintf(1, "width = %d\n", map->scwidth);
	dprintf(1, "height = %d\n", map->scheight);

	dprintf(1, "couleur groupe r = %d, g = %d, b = %d\n", map->pars.ground_r, map->pars.ground_g, map->pars.ground_b);
	dprintf(1, "couleur sky r = %d, g = %d, b = %d\n", map->pars.sky_r, map->pars.sky_g, map->pars.sky_b);

	dprintf(1, "path NO = |%s|\n", map->texture[0].textpath);
	dprintf(1, "path SO = |%s|\n", map->texture[1].textpath);
	dprintf(1, "path EA = |%s|\n", map->texture[2].textpath);
	dprintf(1, "path WE = |%s|\n", map->texture[3].textpath);
	dprintf(1, "path S = |%s|\n", map->text_spr.textpath);
	dprintf(1, "perm = %d\n", map->pars.perm);
*/
	return (0);
}
