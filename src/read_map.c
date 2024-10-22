/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:22:42 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/10/22 19:05:20 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	open_map_file(char *map_file_name)
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

void	init_map_structure(t_game *game, size_t height)
{
	game->map = ft_calloc(1, sizeof(t_map));
	if (!game->map)
	{
		ft_printf("Error\nMemory allocation failed for game->map\n");
		exit(1);
	}
	game->map->full = ft_calloc(height, sizeof(char *));
	if (!game->map->full)
	{
		ft_printf("Error\nMemory allocation failed for game->map->full\n");
		exit(1);
	}
}

void	init_mlx_window(t_game *game) // should thiss be somewhere else????
{
	game->mlx_ptr = mlx_init((game->map_width) * TILESIZE, game->map_height
			* TILESIZE, "~~~~~~ Pac-Ghost ~~~~~~", false);
	if (!game->mlx_ptr)
	{
		free(game);
		exit(1);
	}
}

void	read_map_lines(int fd, t_game *game)
{
	char	*map_line;
	int		i;

	i = 0;
	while (i < game->map_height)
	{
		game->map->full[i] = ft_calloc(game->map_width + 1, sizeof(char));
		map_line = get_next_line(fd);
		if (map_line)
		{
			ft_strlcpy(game->map->full[i], map_line, game->map_width + 1);
			free(map_line);
		}
		else
		{
			ft_printf("Memory allocation failed for map_line");
			exit(1);
		}
		i++;
	}
}

// maybe change function to INT 
void	read_map(char *map_file_name, t_game *game)
{
	int		fd;
	size_t	height;
	size_t	width;

	fd = open_map_file(map_file_name);
	//if (fd == -1)
    //{
    //    perror("Error opening the map file"); // YRS, I am allowwed to use this function. I can also use STRERROR
    //    return ; // Return 0 for failure
    //}
	   // Check if the file is empty
	height = get_map_dimensions(fd, &width);
	//ft_printf("height: %d, width: %d", height, width); /// debugging
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
