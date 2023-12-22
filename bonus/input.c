/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil-moy <sgil-moy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 09:58:47 by sgil-moy          #+#    #+#             */
/*   Updated: 2023/11/21 11:54:12 by sgil-moy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	can_move(t_scene *scene, int dir)
{
	int	x;
	int	y;

	x = scene->player.x;
	y = scene->player.y;
	if (dir == 0)
		y -= 1;
	if (dir == 1)
	{
		scene->player.dir = -1;
		x -= 1;
	}
	if (dir == 2)
		y += 1;
	if (dir == 3)
	{
		scene->player.dir = 1;
		x += 1;
	}
	if (scene->map.map[y][x] == '1' ||
		//scene->map.map[y][x] == '!' ||
		(scene->map.map[y][x] == 'E' &&
		scene->map.can_exit != 1))
		return (-1);
	return (0);
}

void	move(t_scene *scene, int dir)
{
	char	*steps;

	scene->player.dir = dir;
	if (scene->player.can_move != 1 || \
		can_move(scene, dir) != 0)
		return ;
	scene->player.steps++;
	steps = ft_itoa(scene->player.steps);
	write(1, steps, ft_strlen(steps));
	write(1, "\n", 1);
	free (steps);
	scene->map.map[scene->player.y][scene->player.x] = '0';
	if (dir == 0)
		scene->player.y -= 1;
	if (dir == 1)
		scene->player.x -= 1;
	if (dir == 2)
		scene->player.y += 1;
	if (dir == 3)
		scene->player.x += 1;
	scene->player.can_move = -1;
	collisions(scene);
	enemy_turn(scene);
	collisions(scene);
	scene->map.map[scene->player.y][scene->player.x] = 'P';
}

void	collisions(t_scene *scene)
{
	if (scene->map.map[scene->player.y][scene->player.x] == 'C')
	{
		scene->map.map[scene->player.y][scene->player.x] = '0';
		if (check_objs(scene) == 0)
			scene->map.can_exit = 1;
	}
	else if (scene->map.map[scene->player.y][scene->player.x] == 'E' &&
	scene->map.can_exit == 1)
		exit_game(scene);
	else if (scene->map.map[scene->player.y][scene->player.x] == '!')
		exit_game(scene);
}

int	key_hook(int keycode, t_scene *scene)
{
	if (keycode == KEY_W || keycode == KEY_UP)
		move(scene, 0);
	if (keycode == KEY_A || keycode == KEY_LEFT)
		move(scene, 1);
	if (keycode == KEY_S || keycode == KEY_DOWN)
		move(scene, 2);
	if (keycode == KEY_D || keycode == KEY_RIGHT)
		move(scene, 3);
	if (keycode == KEY_ESCAPE)
		exit_game(scene);
	return (0);
}

int	close_win(t_scene *scene)
{
	exit_game(scene);
	return (0);
}
