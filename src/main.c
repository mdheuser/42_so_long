/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:58:48 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/10/18 15:45:11 by mdahlstr         ###   ########.fr       */
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

void    render_map(t_game *game);
void    find_character_position(t_game *game);
void    initialise_game(t_game *game);
void    render_background(t_game *game, int y, int x);
void    render_walls(t_game *game, int y, int x);
void    render_collectibles(t_game *game, int y, int x);
void    render_exit(t_game *game, int y, int x);
void    render_player(t_game *game);
void    free_resources(t_game *game);
void    count_moves(t_game *game);

void    free_resources(t_game *game)
{   
    int i;

    i = 0;
    while (game->map->full[i] != NULL)
    {
        free(game->map->full[i]);
        i++;
    }
    free(game->map->full);
    free(game);
    mlx_terminate(game->mlx_ptr);
}


void    count_moves(t_game *game)
{
    game->move_count++;
}

////////////////////////////////////////////////////////////////////////////// TEMPORARY DEBUGGING
void print_map(t_game *game)
{
    int y = 0;
    while (y < game->map_height)
    {
        ft_printf("%s\n", game->map->full[y]);
        y++;
    }
}
/////////////////////////////////////////////////////////////////////////////////

void    count_collectibles(t_game *game)
{
    int i;
    int j;

    i = 0;
    while (game->map->full[i] != NULL)
    {
        j = 0;
        while (game->map->full[i][j] != '\0' && game->map->full[i][j] != '\n')
        {
            if (game->map->full[i][j] == COLLECTIBLE)
                game->collectible_count++;
            j++;
        }
        i++;
    }
    ft_printf("\ncollectible count: %d\n", game->collectible_count);
}

void    initialise_game(t_game *game)
{
    count_collectibles(game);
    game->score = game->collectible_count;
    game->move_count = 0;
}

void    clear_old_position(t_game *game, int old_y, int old_x)
{
    char old_tile;
    
    //old_tile = game->map->full[game->map->player.y][game->map->player.x];
    //old_tile = game->map->full[old_y][old_x];
    old_tile = game->map->player.standing_on;
    if (old_tile == BACKGROUND || old_tile == COLLECTIBLE)
        render_background(game, old_y, old_x);
    else if (old_tile == EXIT || old_tile == EXIT_OPEN)
        render_exit(game, old_y, old_x);
    
    print_map(game); //////////////////////////////////////////////////DEBUGGING
}

void    set_new_position(t_game *game, int new_y, int new_x)
{
    // Update what was under the player before moving
    game->map->player.standing_on = game->map->full[new_y][new_x];
    
    // Update player position
    game->map->player.x = new_x;
    game->map->player.y = new_y;

    // Render player at new position
    render_player(game);
    //count_moves(game); // something is wrong
}

void    open_exit(t_game *game)
{
    int exit_x;
    int exit_y;

    exit_x = game->map->exit.x;
    exit_y = game->map->exit.y;
    game->map->full[exit_y][exit_x] = EXIT_OPEN;
    render_exit(game, exit_y, exit_x);
}

void    keep_score(t_game *game)
{
    int x;
    int y;

    x = game->map->player.x;
    y = game->map->player.y;
    game->score--;
    game->map->full[y][x] = BACKGROUND; // Replace 'C' with '0'
    if (game->score == 0)
    {
        open_exit(game);
        ft_printf("\n\nYou've killed ALL Pac-Men!\nWell done!\n");
    }
    else
        ft_printf("%d out of %d Pac-Men killed.\n", game->score, game->collectible_count);
}

void    win_game(t_game *game)
{
    if (game->score == 0)
    {
        ft_printf("Good ghost.\nYou've finished the game with %d moves.\n", game->move_count);
        exit(EXIT_SUCCESS);
    }   
}

void    update_character_position(t_game *game, int new_x, int new_y)
{
    int     old_x;
    int     old_y;
    char    new_tile;

    old_x = game->map->player.x;
    old_y = game->map->player.y;
    new_tile = game->map->full[new_y][new_x];
    ft_printf("Current Position: x = %d, y = %d\n", old_x, old_y);
    clear_old_position(game, old_y, old_x);
    set_new_position(game, new_y, new_x);
    if (new_tile == COLLECTIBLE)
    {
        keep_score(game);
        game->map->player.standing_on = BACKGROUND;
    }
    else if (new_tile == EXIT_OPEN)
        win_game(game);
    ft_printf("Updated Position: x = %d, y = %d\n", new_x, new_y);
}

// ATTENTION! This function also turns the initial character position into a background tile!
void    find_character_position(t_game *game)
{
    int i;
    int j;

    i = 0;
    while (i < game->map_height)
    {
        j = 0;
        while (j < game->map_width)
        {
            if (game->map->full[i][j] == PLAYER)
            {
                game->map->player.x = j;
                game->map->player.y = i;
                game->map->player.standing_on = BACKGROUND;
                ft_printf("Initial character position: x = %d, y = %d\n", game->map->player.x, game->map->player.y);
                return ;
            }
            j++;
        }
    i++;
    }
    ft_printf("Character not found in the map.\n");
}

int can_move(t_game *game, int new_x, int new_y)
{
    if (new_y < 0 || new_y >= game->map_height || new_x < 0 || new_x >= game->map_width)
        return (0);
    else if (game->map->full[new_y][new_x] == WALL)
    {
        ft_printf("You cannot go through walls!                     \r");
        return (0);
    }
    return (1);
}

void ft_hook(void *param)
{   
    t_game *game;
    int new_x;
    int new_y;

    game = (t_game *)param;
    new_x = game->map->player.x;
    new_y = game->map->player.y;
    /*
    if (game->move_cooldown > 0)
    {
        game->move_cooldown--;  // Decrement cooldown and skip movement
        return;
    }
    */
    if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx_ptr);
	else if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_UP))
        new_y -= 1;
	else if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_DOWN))
        new_y += 1;
	else if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_LEFT))
        new_x -= 1;
	else if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_RIGHT))
        new_x += 1;
    if (can_move(game, new_x, new_y))
    {
        update_character_position(game, new_x, new_y);
        ft_printf("New player position: x = %d, y = %d\r", new_x, new_y);  // Debugging line
    }
    //game->move_cooldown = MOVE_DELAY;
}

size_t     get_map_dimensions(int fd, size_t *width)
{
    char    *line;
    size_t  height;
    size_t  line_len;
    
    line = get_next_line(fd);
    if (!line)
        return (0);
    line_len = ft_strlen(line);
    if (line[line_len - 1] == '\n')
        line_len--;
    ft_printf("Line width: %d\n", line_len); // Debugging line
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
        if (line[line_len -1] == '\n') // Exclude newline from the comparison
            line_len--;
        ft_printf("Line width: %d\n", line_len); // Debugging line
        if (line_len != *width)
        {
            free(line);
            ft_printf("Error\nInconsistent map line widths.\n");
            return (0); // Return an error code for inconsistent width
        }
        height++;
        free(line); // Free each line as we go
    }
    // Print dimensions for debugging
    ft_printf("Map dimensions: height = %d, width = %d\n", height, *width);
    return (height);
}


// create separate functions for each item and call them all at once or one by one.
/*
Layered Rendering Approach:
Render Floor: For every tile in the map, first render the floor.
Render Static Elements: Then, for the same tile, render static objects (walls, collectibles, exits) if present.
Render Player: Finally, render the player on top of everything, since the player is a dynamic element that can move around.
*/

void    render_background(t_game *game, int y, int x)
{
    mlx_image_to_window(game->mlx_ptr, game->images->background, x * TILESIZE, y * TILESIZE);
}

void    render_walls(t_game *game, int y, int x)
{
    mlx_image_to_window(game->mlx_ptr, game->images->wall, x * TILESIZE, y * TILESIZE);
}

void    render_collectibles(t_game *game, int y, int x)
{
    mlx_image_to_window(game->mlx_ptr, game->images->collectible, x * TILESIZE, y * TILESIZE);
}

void    render_exit(t_game *game, int y, int x)
{
    if (game->map->full[y][x] == EXIT)
    {
        mlx_image_to_window(game->mlx_ptr, game->images->exit, x * TILESIZE, y * TILESIZE);
        game->map->exit.x = x;
        game->map->exit.y = y;
    }
    else if (game->map->full[y][x] == EXIT_OPEN)
        mlx_image_to_window(game->mlx_ptr, game->images->exit_open, x * TILESIZE, y * TILESIZE);
}

void    render_player(t_game *game)
{
    mlx_image_to_window(game->mlx_ptr, game->images->character, game->map->player.x * TILESIZE, game->map->player.y * TILESIZE);
}


void    render_map(t_game *game)
{
    int     x;
    int     y;
    char    tile;

    // Clear the window with the background image first (EVERY POSITION)
    y = 0;
    while (y < game->map_height)
    {
        x = 0;
        while (x < game->map_width)
        {
            render_background(game, y, x);
            x++;
        }
        y++;
    }
    y = 0;
    // render walls, collectibles and exit
    while (y < game->map_height)
    {   
        x = 0;
        while (x < game->map_width)
        {
            tile = game->map->full[y][x];
            if (tile == WALL)
                render_walls(game, y, x);
            else if (tile == COLLECTIBLE)
                render_collectibles(game, y, x);
            else if (tile == EXIT || tile == EXIT_OPEN)
                render_exit(game, y, x);
            x++;
        }
        y++;
    }
    render_player(game);
}

void    load_images(t_game *game)
{
    game->textures = ft_calloc(1, sizeof(t_textures));
    game->textures->background = mlx_load_png("imgs/bw_background.png");
    game->textures->wall = mlx_load_png("imgs/bw_walls2.png");
    game->textures->collectible = mlx_load_png("imgs/bw_pacman2.png");
    game->textures->character = mlx_load_png("imgs/bw_ghost2.png");
    if (!game->textures->character) 
    {
        ft_printf("Error: Could not load character texture\n"); // probably unnecessary
    }
    game->textures->exit = mlx_load_png("imgs/bw_exit1.png");
    game->textures->exit_open = mlx_load_png("imgs/bw_exit2.png");
    
    if (!game->textures->background || !game->textures->wall || 
    !game->textures->collectible || !game->textures->character || 
    !game->textures->exit || !game->textures->exit_open) 
    {
        ft_printf("Error\nError loading textures\n");
        return ;
    }
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

void start_game(t_game *game)
{
    render_map(game);
    find_character_position(game);
    game->map->full[game->map->player.y][game->map->player.y] = BACKGROUND; // change player position to background only after rendering player.
}

int main(int argc, char **argv)
{
    char    *map_line;
    int     fd;
    t_game  *game;
    int     i;
    size_t  height;
    size_t  width;
    char    *map_file = "maps/map_valid2.ber";
    //if (argc != 2)
    //{
    //    ft_printf("Error: Too many or too few arguments\n");
    //    return (1);
    //}
    //fd = open(argv[1], O_RDONLY);
    (void)argc;
    (void)argv;
    fd = open(map_file, O_RDONLY);
    if (fd <= 0)
    {
        ft_printf("Error: Could not open map file\n");
        return (1);
    }
    game = ft_calloc(1, sizeof(t_game));
    height = get_map_dimensions(fd, &width);
    game->map = ft_calloc(1, sizeof(t_map));
    if (!game->map)
    {
        ft_printf("Memory allocation failed for game->map");
        exit(1); // check this
    }
    //game->map->columns = ft_strlen(game->map->full[0]) - 1;
    game->map->full = ft_calloc(height, sizeof(char *));
    if (!game->map->full)
    {
        ft_printf("Memory allocation failed for game->map->full");
        exit(1); // check this
    }
    game->map_width = width;
    game->map_height = height;
    // Rewind the file descriptor to read the map data /// WHAT IS THIS?
    close(fd);
    game->mlx_ptr = mlx_init((game->map_width) * TILESIZE, game->map_height * TILESIZE, "~~~~~~ Pac-Ghost ~~~~~~", false);
    if (!game->mlx_ptr)
    {
        free(game);
        close(fd);
        return (1);
    }
    fd = open(map_file, O_RDONLY);  // Reopen the file 
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
    //////////////////////////////////////////////////////////////////////////////
    print_map(game);
    /////////////////////////////////////////////////////////////////////////////////
    
    load_images(game);
    initialise_game(game);
    start_game(game);
    mlx_loop_hook(game->mlx_ptr, ft_hook, game);
    mlx_loop(game->mlx_ptr);
    free_resources(game);
    close(fd);
    return (0);
}
