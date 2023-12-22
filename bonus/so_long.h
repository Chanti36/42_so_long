/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil-moy <sgil-moy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:41:46 by sgil-moy          #+#    #+#             */
/*   Updated: 2023/11/21 15:53:49 by sgil-moy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# define BUFFER_SIZE 420

# define TILE_EMPTY 		"sprites/bg.xpm"
# define TILE_WALL 			"sprites/bg_wall.xpm"
# define TILE_OBJ			"sprites/coin.xpm"
# define TILE_DOOR_CLOSE	"sprites/exit.xpm"
# define TILE_DOOR_OPEN		"sprites/exit.xpm"

# define TILE_ENEMY_1		"sprites/cat_R_1.xpm"
# define TILE_ENEMY_2		"sprites/cat_R_2.xpm"

# define TILE_PLAYER_L_1	"sprites/p_L_1.xpm"
# define TILE_PLAYER_L_2	"sprites/p_L_2.xpm"
# define TILE_PLAYER_L_3	"sprites/p_L_3.xpm"
# define TILE_PLAYER_L_4	"sprites/p_L_4.xpm"
# define TILE_PLAYER_R_1	"sprites/p_R_1.xpm"
# define TILE_PLAYER_R_2	"sprites/p_R_2.xpm"
# define TILE_PLAYER_R_3	"sprites/p_R_3.xpm"
# define TILE_PLAYER_R_4	"sprites/p_R_4.xpm"

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}	t_vars;

typedef struct s_player
{
	int		dir;
	int		x;
	int		y;
	int		steps;
	int		can_move;
	void	**walk_r_anim;
	void	**walk_l_anim;
	void	*img_r_1;
	void	*img_r_2;
	void	*img_r_3;
	void	*img_r_4;
	void	*img_l_1;
	void	*img_l_2;
	void	*img_l_3;
	void	*img_l_4;
}	t_player;

typedef struct s_enemy
{
	int		x;
	int		y;
	int		dir;
	void	**walk_anim;
	void	*img_1;
	void	*img_2;
}	t_enemy;

typedef struct s_map
{
	char	**map;
	int		start_x;
	int		start_y;
	int		exit_x;
	int		exit_y;
	int		tile_size;
	int		size_x;
	int		size_y;
	int		can_exit;
	void	*img_empty;
	void	*img_wall;
	void	*img_collect;
	void	*img_exit_close;
	void	*img_exit_open;
}	t_map;

typedef struct s_scene
{
	t_player	player;
	t_enemy		enemy;
	t_enemy		*enemies;
	t_map		map;
	t_vars		vars;
	int			size_x;
	int			size_y;
	int			center_x;
	int			center_y;
	int			enemy_count;
	char		*map_dir;
}	t_scene;

enum
{
	KEY_A		= 0,
	KEY_S		= 1,
	KEY_D		= 2,
	KEY_W		= 13,
	KEY_ESCAPE	= 53,
	KEY_LEFT	= 123,
	KEY_RIGHT	= 124,
	KEY_DOWN	= 125,
	KEY_UP		= 126
};

void	print_map(char **map);
int		key_hook(int keycode, t_scene *scene);
void	exit_game(t_scene *scene);
int		close_win(t_scene *scene);
char	*ft_itoa(int n);
size_t	ft_strlen(const char *str);

//initialize
void	initialize_player(void *mlx, t_player *player);
void	initialize_enemies(t_scene *scene);
t_enemy	initialize_enemy(t_scene *scene, int x, int y);
int		initialize_scene(t_vars vars, t_scene *scene);

//render
int		render(t_scene *scene);
void	render_player(t_scene *scene);
void	render_map(t_scene *scene);

//map
int		initialize_map(void *mlx, t_map *map, char *map_dir);
char	**make_map(char *str, t_map *map);
int		map_length(char *str);
int		map_height(char *str);
int		check_map(t_map *map, char *str);
int		check_objs(t_scene *scene);
int		find_rute(char *str, t_map *map);
int		check_format(char *str);
void	*free_map(char **map);

//turn
int		can_move(t_scene *scene, int dir);
void	collisions(t_scene *scene);

//enemy
void	enemy_turn(t_scene *scene);

//gnl
char	*ft_get_line(char *buff);
char	*ft_resize_buff(char *buff);
char	*get_text(char *buff, int fd);
char	*result(char **buff, char *aux);
char	*get_next_line(int fd);
int		ft_find_line(char *buff);
char	*ft_substr(char const *s, unsigned int str, size_t len);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char *s1, char const *s2);
#endif
