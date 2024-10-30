/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:50:02 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/10/30 11:24:49 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libs/libft/libft.h" // includes get_next_line
# include "../libs/mlx/include/MLX42/MLX42.h" // For MiniLibX functions
# include <stdio.h> // For printf, perror
# include <stdlib.h> // For malloc, free, exit
# include <string.h> // For strerror
# include <unistd.h> // For read, write, close
# include <fcntl.h> // For open

# define BACKGROUND		'0'
# define WALL			'1'
# define COLLECTIBLE	'C'
# define EXIT			'E'
# define PLAYER			'P'

# define EXIT_OPEN		'X'

# define TILESIZE		64
# define MOVE_DELAY		6

typedef struct s_position
{
	int		x;
	int		y;
	char	standing_on;
}	t_position;

typedef struct s_textures
{
	mlx_texture_t	*background;
	mlx_texture_t	*wall;
	mlx_texture_t	*collectible;
	mlx_texture_t	*player;
	mlx_texture_t	*exit;
	mlx_texture_t	*exit_open;
}	t_textures;

typedef struct s_images
{
	mlx_image_t	*background;
	mlx_image_t	*wall;
	mlx_image_t	*collectible;
	mlx_image_t	*player;
	mlx_image_t	*exit;
	mlx_image_t	*exit_open;
}	t_images;

typedef struct s_map
{
	char		**full;
	t_position	player;
	t_position	tiles_to_render;
	t_position	exit;
}	t_map;

typedef struct s_game
{
	mlx_t		*mlx_ptr;
	mlx_t		*win_ptr;
	t_textures	*textures;
	t_images	*images;
	t_map		*map;
	int			map_width;
	int			map_height;
	int			score;
	int			collectible_count;
	int			move_count;
	int			move_cooldown;
	int			exit_flag;
	int			player_count;
	int			exit_count;
}	t_game;

void	validate_args(int argc, char *map_file_name);
int		initialise_game(t_game *game, char *map_name);
void	read_map(char *map_file_name, t_game *game);
size_t	get_map_dimensions(int fd, size_t *width);
void	validate_map(t_game *game);
void	validate_path(t_game *game);
void	load_images(t_game *game);
void	free_images(t_game *game);
void	free_textures(t_game *game);
void	render_static_map(t_game *game);
int		render_background(t_game *game, int y, int x);
int		render_collectibles(t_game *game, int y, int x);
int		render_exit(t_game *game, int y, int x);
int		render_player(t_game *game);
int		render_walls(t_game *game, int y, int x);
void	manage_motion(t_game *game);
void	update_player_position(t_game *game, int new_x, int new_y);
void	open_exit(t_game *game);
void	clear_old_position(t_game *game, int old_y, int old_x);
void	set_new_position(t_game *game, int new_y, int new_x);
void	win_game(t_game *game);
void	keep_score(t_game *game);
void	count_moves(t_game *game);
void	handle_error(const char *message, t_game *game);
void	cleanup_game(t_game *game);

#endif