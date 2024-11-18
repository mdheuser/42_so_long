/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:22:42 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/11/15 12:27:00 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Open map file
// Close it if file descriptor (fd) is invalid.
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

	game->map = ft_calloc(1, sizeof(t_map));
	if (!game->map)
	{
		ft_printf("Error\nMemory allocation failed for game->map\n");
		cleanup_game(game);
		exit(1);
	}
	game->map->full = ft_calloc(height, sizeof(char *));
	if (!game->map->full)
	{
		ft_printf("Error\nMemory allocation game->map->full\n");
		cleanup_game(game);
		exit(1);
	}
	i = 0;
	while (i < height)
	{
		game->map->full[i] = NULL;
		i++;
	}
}

// Helper function to handle map_line allocation error
// related to one edge case in get_next_line
// where if reading one line failed, the entire map should be
// read to the end before freeing allocated memory.
static void	handle_allocation_error(int fd, t_game *game, char *map_line)
{
	free(map_line);
	while (1)
	{
		map_line = get_next_line(fd);
		if (!map_line)
			break ;
		free(map_line);
	}
	close(fd);
	handle_error("Memory allocation failed for line.", game);
}

// Read map line one by one using get_next_line()
// Check if the first line is empty.
// Inside the loop: Process the first line and continue reading remaining lines
// Handle case where file ends prematurely
static void	read_map_lines(int fd, t_game *game)
{
	char	*map_line;
	int		i;

	i = 0;
	while (i < game->map_height)
	{
		map_line = get_next_line(fd);
		if (!map_line)
		{
			if (i < game->map_height)
				handle_error("Empty map file.", game);
			else
				handle_error("Unexpected end of file.", game);
		}
		game->map->full[i] = ft_calloc(game->map_width + 1, sizeof(char));
		if (!game->map->full[i])
			handle_allocation_error(fd, game, map_line);
		ft_strlcpy(game->map->full[i], map_line, game->map_width + 1);
		free(map_line);
		i++;
	}
}

// Get's map dimensions and copies the file map
// into a 2d array for use in the game.
// Closes the file descriptor (fd) if valid.
// Handles error and exits the game if file is too big:
// Map size limit width: 60, height: 32.
// (This limit is based on my current computer screen size).
void	read_map(char *map_file_name, t_game *game)
{
	int		fd;
	size_t	height;
	size_t	width;

	width = 0;
	fd = open_map_file(map_file_name);
	height = get_map_dimensions(fd, &width);
	init_map_structure(game, height);
	game->map_width = width;
	game->map_height = height;
	if (fd >= 0)
		close(fd);
	fd = open_map_file(map_file_name);
	read_map_lines(fd, game);
	if (fd >= 0)
		close(fd);
	if (width > 60 || height > 32)
		handle_error("The map is too big.", game);
}
