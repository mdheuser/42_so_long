/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:50:02 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/10/28 20:34:33 by mdahlstr         ###   ########.fr       */
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

typedef struct	s_position
{
	int		x;
	int		y;
	char	standing_on;
} t_position;

typedef struct s_textures
{
	mlx_texture_t	*background;
	mlx_texture_t	*wall;
	mlx_texture_t	*collectible;
	mlx_texture_t	*player;
	mlx_texture_t	*exit;
	mlx_texture_t	*exit_open;
}	t_textures;

typedef struct s_images {
	mlx_image_t	*background;
	mlx_image_t	*wall;
	mlx_image_t	*collectible;
	mlx_image_t	*player;
	mlx_image_t	*exit;
	mlx_image_t	*exit_open;
}	t_images;

typedef struct	s_map
{
	char		**full;
	t_position	player;
	t_position	tiles_to_render;
	t_position	exit;
} t_map;

typedef struct s_game
{
	mlx_t		*mlx_ptr; // MLX pointer
	mlx_t		*win_ptr; // MLX window pointer
	t_textures	*textures; // MLX image pointers (on the stack)
	t_images	*images;
	t_map		*map; // Map pointer (contains map details - preferably kept on the stack)
	int			map_width;
	int			map_height;
	int			score; // initialise it to 0 somewhere! ///////////////////////////////////////// TO DO
	int			collectible_count; // initialise it to 0 somewhere! ///////////////////////////////////////// TO DO
	int			move_count;
	int			move_cooldown;
}	t_game;

// validate_args.c
int	validate_args(int argc, char *map_file_name);

// INITIALISATION /////////////////////////////////////////////////
// initialise_game.c
int	initialise_game(t_game *game, char *map_name);
//t_game* init_game(void);


// read_map.c & get_map_dimensions.c
int	read_map(char *map_file_name, t_game *game);
size_t	get_map_dimensions(int fd, size_t *width);

// validate_map.c
int		validate_map(t_game *game);

// validate_path.c
int		validate_path(t_game *game);

// load_images.c
int    load_images(t_game *game);


int	init_mlx_window(t_game *game);

// render_static_map.c and render_images.c
int		render_static_map(t_game *game);
int		render_background(t_game *game, int y, int x);
int		render_collectibles(t_game *game, int y, int x);
int		render_exit(t_game *game, int y, int x);
int		render_player(t_game *game);
int		render_walls(t_game *game, int y, int x);

// manage_motion
void    manage_motion(t_game *game);
void    open_exit(t_game *game);
void    clear_old_position(t_game *game, int old_y, int old_x);
void    set_new_position(t_game *game, int new_y, int new_x);

// UTILS ////////////////////////////////////////////////////
// counters.c
void    keep_score(t_game *game);
void    count_moves(t_game *game);

// Freeing memory
//void	free_all(t_game *game);
void	cleanup_game(t_game *game);
void	free_images(t_game *game);
void	free_textures(t_game *game);


//void	free_double_p(char ***array);

//win_game.c
void    win_game(t_game *game);

#endif