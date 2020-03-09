/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manaccac <manaccac@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 13:20:57 by manaccac          #+#    #+#             */
/*   Updated: 2020/03/09 13:08:42 by manaccac         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

int				ft_parsing_start(char *s, t_map *map)
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
	ft_puterror(map, "Error Resolution\n");
	free(map->pars.width_str);
	free(map->pars.height_str);
	free(str);
	return (0);
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
	return (ft_parsing_ground_sky_two(str, i, map));
}

int				ft_parsing_ground_sky_two(char *str, int i, t_map *map)
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
	ft_puterror(map, "Error Colors\n");
	free(str);
	return (0);
}
