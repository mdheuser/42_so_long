/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:50:02 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/10/22 18:13:30 by mdahlstr         ###   ########.fr       */
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
# include <math.h> // For math library functions (link with -lm)

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
	void		*mlx_ptr; // MLX pointer
	void		*win_ptr; // MLX window pointer
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

// Functions

int		open_map_file(char *map_file_name);
void	init_map_structure(t_game *game, size_t height);
void	init_mlx_window(t_game *game);
void	read_map_lines(int fd, t_game *game);
void	read_map(char *map_file_name, t_game *game);
void	check_map(t_game *game);
int		validate_map(t_game *game);
int		check_walls(t_game *game, char tile, int x, int y);

// check path -------


void    render_static_map(t_game *game);
void	cover_background(t_game *game);

void    initialise_game(t_game *game);
void    find_player_position(t_game *game);

void    render_background(t_game *game, int y, int x);
void    render_walls(t_game *game, int y, int x);
void    render_collectibles(t_game *game, int y, int x);
void    render_exit(t_game *game, int y, int x);
void    render_player(t_game *game);

void    free_resources(t_game *game);
void    clear_old_position(t_game *game, int old_y, int old_x);
void	check_args(int argc, char *map_file_name);

size_t	get_map_dimensions(int fd, size_t *width);
size_t  find_width(char *line);
size_t  find_height(int fd, char *line, size_t height, size_t *width);
int		validate_map(t_game *game);
int		find_path(t_game *game, int x, int y, char **visited, char target);
int		check_valid_chars(char tile);
int		check_walls(t_game *game, char tile, int x, int y);

// Freeing memory
void	free_double_p(char ***array);



void    load_images(t_game *game);
void    textures_to_image(t_game *game);
void    load_textures(t_game *game);
void    delete_textures(t_game *game);
void	ft_hook(void *param);
void    manage_motion(t_game *game);
int		can_move(t_game *game, int new_x, int new_y);
void    update_player_position(t_game *game, int new_x, int new_y);
void    clear_old_position(t_game *game, int old_y, int old_x);
void    set_new_position(t_game *game, int new_y, int new_x);
void    count_moves(t_game *game);
//void    count_collectibles(t_game *game); // coollectibles are now counted at validate_map
void    keep_score(t_game *game);
void    win_game(t_game *game);
void    open_exit(t_game *game);

//void    close_game(t_game *game);

#endif