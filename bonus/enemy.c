/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil-moy <sgil-moy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:45:21 by sgil-moy          #+#    #+#             */
/*   Updated: 2023/11/21 14:18:21 by sgil-moy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	possible_move(char **map, int x, int y)
{
	if (map[y][x] != '1' && map[y][x] != 'C' && \
		map[y][x] != '!' && map[y][x] != 'E')
		return (1);
	else
		return (0);
}

int	enemy_possible_move(t_enemy *enemy, t_scene *scene, int move_dir)
{
	int	move;

	if (move_dir == 0 && \
		possible_move(scene->map.map, enemy->x, enemy->y - 1))
		move = 0;
	else if (move_dir == 1 && \
		possible_move(scene->map.map, enemy->x - 1, enemy->y))
		move = 1;
	else if (move_dir == 2 && \
		possible_move(scene->map.map, enemy->x, enemy->y + 1))
		move = 2;
	else if (move_dir == 3 && \
		possible_move(scene->map.map, enemy->x + 1, enemy->y))
		move = 3;
	else if (possible_move(scene->map.map, enemy->x, enemy->y - 1) == 1)
		move = 0;
	else if (possible_move(scene->map.map, enemy->x - 1, enemy->y) == 1)
		move = 1;
	else if (possible_move(scene->map.map, enemy->x, enemy->y + 1) == 1)
		move = 2;
	else if (possible_move(scene->map.map, enemy->x + 1, enemy->y) == 1)
		move = 3;
	else
		move = -1;
	return (move);
}

void	enemy_move(t_enemy *enemy, t_scene *scene, int move_dir)
{
	int	move;

	move = enemy_possible_move(enemy, scene, move_dir);
	if (move == -1)
		return ;
	scene->map.map[enemy->y][enemy->x] = '0';
	if (move == 0)
		enemy->y -= 1;
	if (move == 1)
	{
		enemy->x -= 1;
		enemy->dir = -1;
	}
	if (move == 2)
		enemy->y += 1;
	if (move == 3)
	{
		enemy->x += 1;
		enemy->dir = 1;
	}
	scene->map.map[enemy->y][enemy->x] = '!';
}

void	enemy_turn(t_scene *scene)
{
	int			i;
	static int	rng_move;

	++rng_move;
	if (rng_move > 99)
		rng_move = 0;
	i = 0;
	while (i < scene->enemy_count)
	{
		enemy_move(&scene->enemies[i], scene, rng_move / 25);
		++i;
	}
	scene->player.can_move = 1;
}
