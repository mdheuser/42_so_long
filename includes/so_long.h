/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:50:02 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/10/21 13:40:20 by mdahlstr         ###   ########.fr       */
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
// # define MOVE_DELAY		10

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
	mlx_texture_t	*character;
	mlx_texture_t	*exit;
	mlx_texture_t	*exit_open;
}	t_textures;

typedef struct s_images {
	mlx_image_t	*background;
	mlx_image_t	*wall;
	mlx_image_t	*collectible;
	mlx_image_t	*character;
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
	// int			move_cooldown;
}	t_game;

//void    parse_command_line_args(int argc, char  **argv, t_game *game);
//void    close_game(t_game *game);

/*
from: https://reactive.so/post/42-a-comprehensive-guide-to-so_long/ */

// char **load_map(const char *file_path);

#endif