/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil-moy <sgil-moy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 10:42:34 by sgil-moy          #+#    #+#             */
/*   Updated: 2023/11/23 11:43:23 by sgil-moy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	render_player(t_scene *scene)
{
	void		*char_image;
	static int	anim;

	++anim;
	if (anim > 99)
		anim = 0;
	if (scene->player.dir == 1)
		char_image = scene->player.walk_r_anim[anim / 25];
	else
		char_image = scene->player.walk_l_anim[anim / 25];
	mlx_put_image_to_window (scene->vars.mlx, scene->vars.win, char_image,
		((scene->player.x) * scene->map.tile_size),
		scene->size_y / 2 + ((-(scene->map.size_y / 2) + scene->player.y) \
		* scene->map.tile_size));
}

void	render_item(t_scene *scene, void *item, int i, int j)
{
	if (item != NULL)
		mlx_put_image_to_window (scene->vars.mlx, scene->vars.win, item,
			(j * scene->map.tile_size),
			scene->size_y / 2 + ((-(scene->map.size_y / 2) + i) \
			* scene->map.tile_size));
}

void	render_scene_items(t_scene *scene, int anim)
{
	int		i;
	int		j;
	void	*tile;

	i = 0;
	while (scene->map.map[i])
	{
		j = 0;
		while (scene->map.map[i][j])
		{
			tile = NULL;
			if (scene->map.map[i][j] == '!')
				tile = scene->enemy.walk_anim[anim / 25];
			else if (scene->map.map[i][j] == 'C')
				tile = scene->map.img_collect;
			else if (scene->map.map[i][j] == 'E' && scene->map.can_exit)
					tile = scene->map.img_exit_open;
			else if (scene->map.map[i][j] == 'E' && !scene->map.can_exit)
					tile = scene->map.img_exit_close;
			render_item(scene, tile, i, j);
			++j;
		}
		++i;
	}
}

void	render_map(t_scene *scene)
{
	int		i;
	int		j;
	void	*tile;

	i = 0;
	while (scene->map.map[i])
	{
		j = 0;
		while (scene->map.map[i][j])
		{
			if (scene->map.map[i][j] == '1')
				tile = scene->map.img_wall;
			else
				tile = scene->map.img_empty;
			mlx_put_image_to_window (scene->vars.mlx, scene->vars.win, tile,
				(j * scene->map.tile_size),
				scene->size_y / 2 + ((-(scene->map.size_y / 2) + i) * \
				scene->map.tile_size));
			++j;
		}
		++i;
	}
}

int	render(t_scene *scene)
{
	char		*steps;
	static int	anim;

	++anim;
	if (anim > 49)
		anim = 0;
	steps = ft_itoa(scene->player.steps);
	mlx_clear_window(scene->vars.mlx, scene->vars.win);
	render_map(scene);
	render_scene_items(scene, anim);
	render_player(scene);
	mlx_string_put(scene->vars.mlx, scene->vars.win, \
	scene->size_x * 0.5, scene->size_y * 0.8, 0x1BF3C8, steps);
	free(steps);
	return (0);
}
