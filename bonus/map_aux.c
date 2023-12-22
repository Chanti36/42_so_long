/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_aux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil-moy <sgil-moy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:08:55 by sgil-moy          #+#    #+#             */
/*   Updated: 2023/11/21 14:15:51 by sgil-moy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	map_length(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\n')
		++i;
	return (i);
}

int	map_height(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (str[i])
	{
		if (str[i] == '\n')
			++j;
		++i;
	}
	return (j);
}

void	explore_path(int x, int y, char **rute_map)
{
	if (rute_map[y][x] == 'E')
	{
		rute_map[y][x] = '1';
		return ;
	}
	rute_map[y][x] = '1';
	if (rute_map[y - 1][x] != '1')
		explore_path(x, y - 1, rute_map);
	if (rute_map[y + 1][x] != '1')
		explore_path(x, y + 1, rute_map);
	if (rute_map[y][x - 1] != '1')
		explore_path(x - 1, y, rute_map);
	if (rute_map[y][x + 1] != '1')
		explore_path(x + 1, y, rute_map);
}

int	check_paths(char **rute_map)
{
	int	i;
	int	j;

	i = 0;
	while (rute_map[i])
	{
		j = 0;
		while (rute_map[i][j])
		{
			if (rute_map[i][j] == 'C' || rute_map[i][j] == 'E')
				return (-1);
			++j;
		}
		++i;
	}
	return (1);
}

int	find_rute(char *str, t_map *map)
{	
	int		result;
	char	**rute_map;

	rute_map = make_map(str, map);
	if (!rute_map)
		return (-1);
	explore_path(map->start_x, map->start_y, rute_map);
	result = check_paths(rute_map);
	free_map(rute_map);
	return (result);
}
