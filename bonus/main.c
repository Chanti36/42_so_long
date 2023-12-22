/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil-moy <sgil-moy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:41:31 by sgil-moy          #+#    #+#             */
/*   Updated: 2023/11/21 13:08:06 by sgil-moy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	print_map(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			++j;
			printf("%c", map[i][j]);
		}
		printf("\n");
		++i;
	}
	printf("\n___________________________________________________\n");
}

void	exit_game(t_scene *scene)
{
	free_map(scene->map.map);
	mlx_destroy_window(scene->vars.mlx, scene->vars.win);
	exit(1);
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	t_scene	scene;

	if (argc != 2)
		return (0);
	else
		scene.map_dir = argv[1];
	vars.mlx = mlx_init();
	if (check_format(scene.map_dir) == 0 || \
		initialize_scene(vars, &scene) == -1)
	{
		write(1, "Error\n", 6);
		return (0);
	}
	vars.win = mlx_new_window(vars.mlx, scene.size_x, scene.size_y, "joego");
	scene.vars = vars;
	mlx_hook(scene.vars.win, 2, 0, key_hook, &scene);
	mlx_hook(scene.vars.win, 17, 0, close_win, &scene);
	mlx_loop_hook(scene.vars.mlx, render, &scene);
	mlx_loop(scene.vars.mlx);
	return (1);
}
