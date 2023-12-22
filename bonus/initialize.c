/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil-moy <sgil-moy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 11:21:01 by sgil-moy          #+#    #+#             */
/*   Updated: 2023/11/21 14:17:16 by sgil-moy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	initialize_player(void *mlx, t_player *player)
{
	int	size;

	size = 48;
	player->steps = 0;
	player->can_move = 1;
	player->img_r_1 = mlx_xpm_file_to_image(mlx, TILE_PLAYER_R_1, &size, &size);
	player->img_r_2 = mlx_xpm_file_to_image(mlx, TILE_PLAYER_R_2, &size, &size);
	player->img_r_3 = mlx_xpm_file_to_image(mlx, TILE_PLAYER_R_3, &size, &size);
	player->img_r_4 = mlx_xpm_file_to_image(mlx, TILE_PLAYER_R_4, &size, &size);
	player->walk_r_anim = (void *)malloc(sizeof(void *) * 4);
	player->walk_r_anim[0] = player->img_r_1;
	player->walk_r_anim[1] = player->img_r_2;
	player->walk_r_anim[2] = player->img_r_3;
	player->walk_r_anim[3] = player->img_r_4;
	player->img_l_1 = mlx_xpm_file_to_image(mlx, TILE_PLAYER_L_1, &size, &size);
	player->img_l_2 = mlx_xpm_file_to_image(mlx, TILE_PLAYER_L_2, &size, &size);
	player->img_l_3 = mlx_xpm_file_to_image(mlx, TILE_PLAYER_L_3, &size, &size);
	player->img_l_4 = mlx_xpm_file_to_image(mlx, TILE_PLAYER_L_4, &size, &size);
	player->walk_l_anim = (void *)malloc(sizeof(void *) * 4);
	player->walk_l_anim[0] = player->img_l_1;
	player->walk_l_anim[1] = player->img_l_2;
	player->walk_l_anim[2] = player->img_l_3;
	player->walk_l_anim[3] = player->img_l_4;
}

t_enemy	initialize_enemy(t_scene *scene, int x, int y)
{
	t_enemy	new_enemy;
	int		size;

	size = 48;
	new_enemy.x = x;
	new_enemy.y = y;
	new_enemy.dir = 1;
	new_enemy.img_1 = mlx_xpm_file_to_image \
		(scene->vars.mlx, TILE_ENEMY_1, &scene->map.tile_size, \
		&scene->map.tile_size);
	new_enemy.img_2 = mlx_xpm_file_to_image \
		(scene->vars.mlx, TILE_ENEMY_2, &size, &size);
	new_enemy.walk_anim = (void *)malloc(sizeof(void *) * 5);
	new_enemy.walk_anim[0] = new_enemy.img_1;
	new_enemy.walk_anim[1] = new_enemy.img_2;
	new_enemy.walk_anim[2] = NULL;
	return (new_enemy);
}

int	count_enemies(t_scene *scene)
{
	int		i;
	int		j;
	int		enemies;

	enemies = 0;
	i = 0;
	while (scene->map.map[i])
	{
		j = 0;
		while (scene->map.map[i][j])
		{
			if (scene->map.map[i][j] == '!')
				enemies++;
			++j;
		}
		++i;
	}
	return (enemies);
}

void	initialize_enemies(t_scene *scene)
{
	int	i;
	int	j;
	int	index;

	scene->enemy_count = count_enemies(scene);
	scene->enemies = (t_enemy *)malloc(sizeof(t_enemy) * scene->enemy_count);
	i = 0;
	index = 0;
	while (scene->map.map[i])
	{
		j = 0;
		while (scene->map.map[i][j])
		{
			if (scene->map.map[i][j] == '!')
			{
				scene->enemies[index] = initialize_enemy(scene, j, i);
				++index;
			}
			++j;
		}
		++i;
	}
}

int	initialize_scene(t_vars vars, t_scene *scene)
{
	t_player	new_player;
	t_enemy		new_enemy;
	t_map		new_map;

	initialize_player(vars.mlx, &new_player);
	if (initialize_map(vars.mlx, &new_map, scene->map_dir) == -1)
		return (-1);
	new_player.x = new_map.start_x;
	new_player.y = new_map.start_y;
	scene->vars = vars;
	scene->player = new_player;
	scene->map = new_map;
	scene->size_x = scene->map.size_x * 48;
	scene->size_y = scene->map.size_y * 48 * 2;
	scene->map.tile_size = 48;
	scene->center_x = scene->size_x / 2;
	scene->center_y = scene->size_y / 2;
	new_enemy = initialize_enemy(scene, -100, -100);
	initialize_enemies(scene);
	scene->enemy = new_enemy;
	return (1);
}
