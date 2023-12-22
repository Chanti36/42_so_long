/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil-moy <sgil-moy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:44:35 by sgil-moy          #+#    #+#             */
/*   Updated: 2023/11/21 12:12:50 by sgil-moy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_limits(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\n')
	{
		if (str[i] != '1')
			return (-1);
		++i;
	}
	while (str[i])
	{
		if (str[i] == '\n')
			if (str[i - 1] != '1' || str[i + 1] != '1')
				return (-1);
		++i;
	}
	--i;
	while (str[i] != '\n')
	{
		if (str[i] != '1')
			return (-1);
		--i;
	}
	return (1);
}

int	check_rectangle(char *str)
{
	int	i;
	int	len;
	int	savelen;

	i = 0;
	len = 0;
	savelen = 0;
	while (str[i])
	{
		if (str[i] == '\n' || str[i] == '\0')
		{
			if (savelen == 0)
				savelen = i;
			else
				if (len != savelen)
					return (-1);
			len = -1;
		}
		++i;
		++len;
	}
	return (0);
}

int	check_obj(char *str)
{
	int	i;
	int	exit;
	int	collect;
	int	start;

	i = 0;
	exit = 0;
	collect = 0;
	start = 0;
	while (str[i])
	{
		if (str[i] == 'E')
			++exit;
		if (str[i] == 'C')
			++collect;
		if (str[i] == 'P')
			++start;
		++i;
	}
	if (start != 1 || exit != 1 || collect < 1)
		return (-1);
	return (0);
}

int	check_map(t_map *map, char *str)
{
	int	i;

	i = 0;
	if (check_limits(str) == -1 || \
		check_rectangle(str) == -1 || \
		check_obj(str) == -1)
		return (-1);
	map->size_x = map_length(str);
	map->size_y = map_height(str);
	while (str[i])
	{
		if (str[i] == 'P')
		{
			map->start_x = (i - (i / map->size_x)) % map->size_x;
			map->start_y = (i - (i / map->size_x)) / map->size_x;
		}
		if (str[i] == 'E')
		{
			map->exit_x = (i - (i / map->size_x)) % map->size_x;
			map->exit_y = (i - (i / map->size_x)) / map->size_x;
		}
		++i;
	}
	return (0);
}

int	check_format(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		++i;
	if (str[i - 1] != 'r')
		return (0);
	if (str[i - 2] != 'e')
		return (0);
	if (str[i - 3] != 'b')
		return (0);
	if (str[i - 4] != '.')
		return (0);
	return (1);
}
