/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil-moy <sgil-moy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:02:26 by sgil-moy          #+#    #+#             */
/*   Updated: 2023/11/21 12:59:46 by sgil-moy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>
#include <sys/stat.h>

void	*free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
	return (NULL);
}

char	**make_map(char *str, t_map *map)
{
	int		i;
	int		j;
	char	**new_map;

	i = 0;
	new_map = (char **)malloc(sizeof(char *) * map->size_y + 1);
	if (!new_map)
		return (NULL);
	while (i < map->size_y)
	{
		j = 0;
		new_map[i] = (char *)malloc(sizeof(char) * (map->size_x + 1));
		if (!new_map[i])
			return (free_map(new_map));
		while (j < map->size_x)
		{
			new_map[i][j] = str[(i * map->size_x) + j + i];
			++j;
		}
		new_map[i][j] = '\0';
		++i;
	}
	new_map[i] = NULL;
	return (new_map);
}

char	*read_map(char *map_dir)
{
	int		file;
	char	*aux;
	char	*str;

	file = open(map_dir, O_RDONLY);
	aux = get_next_line(file);
	str = NULL;
	while (aux != NULL)
	{
		str = ft_strjoin(str, aux);
		free(aux);
		aux = get_next_line(file);
	}
	if (aux)
		free(aux);
	close(file);
	return (str);
}

int	initialize_map(void *mlx, t_map *map, char *map_dir)
{
	char	*str;

	str = read_map(map_dir);
	if (!str)
		return (-1);
	if (check_map(map, str) == -1)
		return (-1);
	map->map = make_map(str, map);
	if (map->map == NULL)
		return (-1);
	if (find_rute(str, map) == -1)
		return (-1);
	map->img_empty = mlx_xpm_file_to_image \
		(mlx, TILE_EMPTY, &map->tile_size, &map->tile_size);
	map->img_wall = mlx_xpm_file_to_image \
		(mlx, TILE_WALL, &map->tile_size, &map->tile_size);
	map->img_collect = mlx_xpm_file_to_image \
		(mlx, TILE_OBJ, &map->tile_size, &map->tile_size);
	map->img_exit_close = mlx_xpm_file_to_image \
		(mlx, TILE_DOOR_CLOSE, &map->tile_size, &map->tile_size);
	map->img_exit_open = mlx_xpm_file_to_image \
		(mlx, TILE_DOOR_OPEN, &map->tile_size, &map->tile_size);
	map->can_exit = 0;
	free(str);
	return (1);
}

int	check_objs(t_scene *scene)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	j = 0;
	while (i < scene->map.size_y)
	{
		j = 0;
		while (j < scene->map.size_x)
		{
			if (scene->map.map[i][j] == 'C')
				++count;
			++j;
		}
		++i;
	}
	return (count);
}
