/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:58:48 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/10/14 21:44:24 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Player movement must update the map->full array.
/*
To add movement to your game, you need to capture key press events and update 
the player's position on the map accordingly. You can follow these steps:

1 . Handle Key Press Events: Use MLX42's event handling to detect when specific keys 
are pressed.
2 . Move the Player: Adjust the player's position based on the key press while 
checking for collisions (walls or boundaries).
3 . Redraw the Map: After moving the player, redraw the map to reflect the new 
position.
4 . Add the key hook to the main function
Finally, add the key hook to your main function so that you can detect key presses and move the player accordingly:
*/

void ft_hook(void* param, t_game *game)
{
	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx_ptr);
	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_UP))
		game->images->character->instances[0].y -= 5;
	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_DOWN))
		game->images->character->instances[0].y += 5;
	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_LEFT))
		game->images->character->instances[0].x -= 5;
	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_RIGHT))
		game->images->character->instances[0].x += 5;
}

int     get_map_dimensions(int fd, int *width)
{
    char    *line;
    int     height;
    
    line = get_next_line(fd);
    if (!line)
        return (0);
    *width = ft_strlen(line);
    free(line);
    height = 1;
    while ((line = get_next_line(fd)) != NULL)
    {
        height++;
        free(line); // Free each line as we go
    } 
    return (height);
}

void    render_game(t_game *game)
{
    int     x;
    int     y;
    char    tile;

    y = 0;
    while (y < game->map_height)
    {   
        x = 0;
        while (x < game->map_width)
        {
            tile = game->map->full[y][x];
            if (tile == WALL) // Wall
                mlx_image_to_window(game->mlx_ptr, game->images->wall, x * TILESIZE, y * TILESIZE);
            else if (tile == SPACE) // Empty space
                mlx_image_to_window(game->mlx_ptr, game->images->background, x * TILESIZE, y * TILESIZE);
            else if (tile == COLLECTIBLE) // Collectible
                mlx_image_to_window(game->mlx_ptr, game->images->collectible, x * TILESIZE, y * TILESIZE);
            else if (tile == EXIT) // Exit
                mlx_image_to_window(game->mlx_ptr, game->images->exit, x * TILESIZE, y * TILESIZE);
            else if (tile == PLAYER) // Player
            {
                mlx_image_to_window(game->mlx_ptr, game->images->character, x * TILESIZE, y * TILESIZE);
                // here I can initialise the player's position.
                // Changes in this position are handled in another function
                // Better to only update the positions that are changed:
                // Player, collectibles, exit (update_map??)
            }
            x++;
        }
        y++;
    }
}

void    update_map(t_game game)
{
    XXXXXX
}
/*
new_player_position(t_game game)
{
    
    game->map->player.x = x;
    game->map->player.y = y;
}
*/

void    load_images(t_game *game)
{
    // textures
    game->textures = ft_calloc(1, sizeof(t_textures));
    game->textures->background = mlx_load_png("imgs/bw_background.png");
    game->textures->wall = mlx_load_png("imgs/bw_walls2.png");
    game->textures->collectible = mlx_load_png("imgs/bw_pacman2.png");
    game->textures->character = mlx_load_png("imgs/bw_ghost.png");
    game->textures->exit = mlx_load_png("imgs/bw_exit1.png");
    game->textures->exit_open = mlx_load_png("imgs/bw_exit2.png");
    
    if (!game->textures->background || !game->textures->wall || 
    !game->textures->collectible || !game->textures->character || 
    !game->textures->exit || !game->textures->exit_open) 
    {
    // Handle the error, e.g., print an error message and return
        ft_printf("Error loading textures\n");
        return;
    }
    // images
    game->images = ft_calloc(1, sizeof(t_images));
    game->images->background = mlx_texture_to_image(game->mlx_ptr, game->textures->background);
    game->images->wall = mlx_texture_to_image(game->mlx_ptr, game->textures->wall);
    game->images->collectible = mlx_texture_to_image(game->mlx_ptr, game->textures->collectible);
    game->images->character = mlx_texture_to_image(game->mlx_ptr, game->textures->character);
    game->images->exit = mlx_texture_to_image(game->mlx_ptr, game->textures->exit);
    game->images->exit_open = mlx_texture_to_image(game->mlx_ptr, game->textures->exit_open);
    mlx_delete_texture(game->textures->background);
	mlx_delete_texture(game->textures->wall);
	mlx_delete_texture(game->textures->collectible);
	mlx_delete_texture(game->textures->character);
	mlx_delete_texture(game->textures->exit);
	mlx_delete_texture(game->textures->exit_open);
}

int main(int argc, char **argv)
{
    char    *map_line;
    int     fd;
    t_game  *game;
    int     i;
    int     height;
    int     width;

    //if (argc != 2)
    //{
    //    ft_printf("Error: Too many or too few arguments\n");
    //    return (1);
    //}
    //fd = open(argv[1], O_RDONLY);
    (void)argc;
    (void)argv;
    //fd = open("maps/map_valid.ber", O_RDONLY);
    fd = open("maps/map_only_walls.ber", O_RDONLY);
    if (fd <= 0)
    {
        ft_printf("Error: Could not open map file\n");
        return (1);
    }
    game = ft_calloc(1, sizeof(t_game));
    height = get_map_dimensions(fd, &width);
    
    game->map = ft_calloc(1, sizeof(t_map));
    //game->map->columns = ft_strlen(game->map->full[0]) - 1;
    game->map->full = ft_calloc(height, sizeof(char *));
    game->map_width = width;
    game->map_height = height;
   
    // Rewind the file descriptor to read the map data /// WHAT IS THIS?
    lseek(fd, 0, SEEK_SET); // ATTENTION!!!!!! /////////////////////////////////
    i = 0;
    while (i < game->map_height)
    {
        game->map->full[i] = ft_calloc(game->map_width + 1, sizeof(char));
        map_line = get_next_line(fd);
        if (map_line)
        {
            //ft_strncpy(game->map->full[i], map_line, game->map_width);
            ft_strlcpy(game->map->full[i], map_line, game->map_width);
            free(map_line);
        }
        i++;
    }
    game->mlx_ptr = mlx_init(game->map_width * TILESIZE, game->map_height * TILESIZE, "PAC-GHOST 👻", false);
    if (!game->mlx_ptr)
    {
        free(game);
        close(fd);
        return (1);
    }
    load_images(game);
    while (1)
    {
        render_game(game);
        mlx_loop_hook(game->mlx_ptr, ft_hook, game);
        mlx_loop(game->mlx_ptr);
    }
    close(fd);
    return (0);
}
