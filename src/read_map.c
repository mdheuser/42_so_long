/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:22:42 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/10/28 17:46:56 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	open_map_file(char *map_file_name)
{
	int	fd;

	fd = open(map_file_name, O_RDONLY);
	if (fd <= 0)
	{
		ft_printf("Error: Could not open map file\n");
		exit(1);
	}
	return (fd);
}

// Initialise game->map & game->map->full
static void	init_map_structure(t_game *game, size_t height)
{
	size_t	i;

	//game->map = NULL;  // Initialize to NULL
    //game->map->full = NULL;  // Initialize to NULL (will be reassigned later)
	game->map = ft_calloc(1, sizeof(t_map));
	if (!game->map)
	{
		ft_printf("Error\nMemory allocation failed for game->map\n");
		//cleanup_game(game);
		exit(1);
	}
	game->map->full = ft_calloc(height, sizeof(char *));
	if (!game->map->full)
	{
		ft_printf("Error\nMemory allocation failed for game->map->full\n");
		//cleanup_game(game);
		exit(1);
	}
	i = 0;
	while (i < height)
    {
        game->map->full[i] = NULL;
		i++;
	}
}

// MOVED THIS FUNCTION TO initialise_game.c
/*static void	init_mlx_window(t_game *game) // should thiss be somewhere else????
{
	game->mlx_ptr = mlx_init((game->map_width) * TILESIZE, game->map_height
			* TILESIZE, "~~~~~~ Pac-Ghost ~~~~~~", false);
	if (!game->mlx_ptr)
	{
		cleanup_game(game);
		exit(1);
	}
}
*/

static void	read_map_lines(int fd, t_game *game) // This is causing problems!!!
{
	char	*map_line;
	int		i;

	// Check if the first line is empty
	map_line = get_next_line(fd);
	if (!map_line)
	{
		ft_printf("Error\nEmpty map file\n");
		close(fd);
		cleanup_game(game);
		exit(1);
	}
	i = 0;
	// Process the first line and continue reading remaining lines
	while (i < game->map_height)
	{
		game->map->full[i] = ft_calloc(game->map_width + 1, sizeof(char));
		if (!game->map->full[i])
		{
			ft_printf("Memory allocation failed for line %d\n", i);
			free(map_line);
			cleanup_game(game);
			exit(1);
		}
		ft_strlcpy(game->map->full[i], map_line, game->map_width + 1);
		free(map_line);
		map_line = get_next_line(fd);
		// Handle case where file ends prematurely
		if (!map_line && i < game->map_height - 1)
		{
			ft_printf("Error: Unexpected end of file\n");
			cleanup_game(game);
			exit(1);
		}
		i++;
	}
	close (fd);
}

// the open_map_file() function handles wrong fd
int	read_map(char *map_file_name, t_game *game)
{
	int		fd;
	size_t	height;
	size_t	width;

	width = 0;
	fd = open_map_file(map_file_name);
	height = get_map_dimensions(fd, &width);
	ft_printf("height: %d, width: %d\n", height, width); /// debugging /////////////
	init_map_structure(game, height);
	game->map_width = width;
	game->map_height = height;
	if (fd >= 0)
		close(fd);
	// init_mlx_window(game); moved this call to initialise_game.c 
	fd = open_map_file(map_file_name);
	read_map_lines(fd, game);
	//if (fd >= 0)
	//	close(fd);
	return (1);
}

/*
void	read_map(char *map_file_name, t_game *game)
{
	int		fd;
	char	buffer[1024];
	size_t	height;
	size_t	width;
	ssize_t	bytes_read;

	fd = open_map_file(map_file_name);
	if (fd == -1)
    {
        perror("Error opening the map file"); // YRS, I am allowwed to use this function. I can also use STRERROR
        return ; // Return 0 for failure
    }
	   // Check if the file is empty
    bytes_read = read(fd, buffer, sizeof(buffer));
    if (bytes_read <= 0)
    {
        close(fd); // Close the file descriptor
        ft_printf("Error: The map file is empty or could not be read.\n");
        return ; // Return 0 for failure // MAYBE CHANGE FUNCTION TO INT 
    }
	height = get_map_dimensions(fd, &width);
	ft_printf("height: %d, width: %d", height, width); /// debugging
	if (height < 3 && width < 3)
	{
		ft_printf("Empty file or map too small"); // something like this?
		return ;
	}
	init_map_structure(game, height);
	game->map_width = width;
	game->map_height = height;
	if (fd >= 0)
		close(fd);
	init_mlx_window(game);
	fd = open_map_file(map_file_name);
	read_map_lines(fd, game);
	if (fd >= 0)
		close(fd);
}
*/
