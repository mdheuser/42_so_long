/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:22:42 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/10/21 20:45:02 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
Get map dimensions
divide it into:
1 . read line and get length
2 . check line width
3 . the function itself
*/


size_t     get_map_dimensions(int fd, size_t *width)
{
    char    *line;
    size_t  height;
    size_t  line_len;
    
    line = get_next_line(fd);
    if (!line)
        return (0);
    line_len = ft_strlen(line);
    while (line_len > 0 && (line[line_len - 1] == '\n' || line[line_len - 1] == '\r'))
        line_len--;
    ft_printf("Line width: %d\n", line_len); // Debugging line
    ft_printf("Line: %s\n", line);
    *width = line_len;
    if (*width == 0)
    {
        free(line);
        return (0);
    }
    height = 1;
    free(line);
    while ((line = get_next_line(fd)) != NULL)
    {
    // Check if each line has the same width
        line_len = ft_strlen(line);
        while (line_len > 0 && (line[line_len - 1] == '\n' || line[line_len - 1] == '\r'))
            line_len--;
        ft_printf("Line width: %d\n", line_len); // Debugging line
        ft_printf("Line: %s\n", line); // Debugging
        if (line_len != *width)
        {
            free(line);
            ft_printf("Error\nInconsistent map line widths.\n");
            exit(1);
            // return (1); // ?????
        }
        height++;
        free(line); // Free each line as we go
    }
    // Print dimensions for debugging
    ft_printf("Map dimensions: height = %d, width = %d\n", height, *width);
    return (height);
}

/////////////////////////////////////////////////////////////////////////
// DIVIDE IT INTO:
// 1. int open_map_file(char *map_file_name)
// 2. void init_map_structure(t_game *game, size_t height)
// 3. size_t get_map_dimensions(int fd, size_t *width) - DONE!
// 4. void init_mlx_window(t_game *game)
// 5. void read_map_lines(int fd, t_game *game)
// 6. void close_map_file(int fd)


// 1. open map file
int open_map_file(char *map_file_name)
{
    int fd;
    
    fd = open(map_file_name, O_RDONLY);
    if (fd <= 0)
    {
        ft_printf("Error: Could not open map file\n");
        exit(1);
    }
    return (fd);
}

void init_map_structure(t_game *game, size_t height)
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

void close_map_file(int fd)
{
    if (fd >= 0)
        close(fd);
}

void init_mlx_window(t_game *game)
{
    game->mlx_ptr = mlx_init((game->map_width) * TILESIZE, game->map_height * TILESIZE, "~~~~~~ Pac-Ghost ~~~~~~", false);
    if (!game->mlx_ptr)
    {
        free(game);
        exit(1);
    }
}

void read_map_lines(int fd, t_game *game)
{
    char    *map_line;
    int     i;

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
            ft_printf("Memory allocation failed for map_line through get_next_line");
            exit(1); // check this
        }
        i++;
    }
}

void    read_map(char *map_file_name, t_game *game)
{   
    int     fd;
    size_t  height;
    size_t  width;
    
    fd = open_map_file(map_file_name);
    height = get_map_dimensions(fd, &width);
    init_map_structure(game, height);
    game->map_width = width;
    game->map_height = height;
    close_map_file(fd);
    init_mlx_window(game);
    fd = open_map_file(map_file_name);
    read_map_lines(fd, game);
    close_map_file(fd);
}