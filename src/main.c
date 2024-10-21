/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:58:48 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/10/21 20:16:06 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void    render_static_map(t_game *game);
void    find_character_position(t_game *game);
void    initialise_game(t_game *game);
void    render_background(t_game *game, int y, int x);
void    render_walls(t_game *game, int y, int x);
void    render_collectibles(t_game *game, int y, int x);
void    render_exit(t_game *game, int y, int x);
void    render_player(t_game *game);
void    free_resources(t_game *game);
void    count_moves(t_game *game);
void    clear_old_position(t_game *game, int old_y, int old_x);



void    count_moves(t_game *game)
{
    ft_printf("Moves: %d\n", game->move_count++);
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
    while (i < game->map_height)
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
    find_character_position(game); // also clears player tile in map->full
    render_player(game);
    count_collectibles(game);
    game->score = game->collectible_count;
    game->move_count = 0;
}

void    clear_old_position(t_game *game, int old_y, int old_x)
{
    char old_tile;
    
    old_tile = game->map->full[old_y][old_x];
    if (old_tile == BACKGROUND || old_tile == COLLECTIBLE)
        render_background(game, old_y, old_x);
    else if (old_tile == EXIT || old_tile == EXIT_OPEN)
        render_exit(game, old_y, old_x);
    //print_map(game);
}

void    set_new_position(t_game *game, int new_y, int new_x)
{
    // Update what was under the player before moving
    game->map->player.standing_on = game->map->full[new_y][new_x];
    
    // Update player position
    game->map->player.x = new_x;
    game->map->player.y = new_y;
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
        count_moves(game);
        ft_printf("Good ghost!\nYou've finished the game with %d moves.\nCan you do fewer?\n", game->move_count);
        exit(EXIT_SUCCESS);
    }   
}

void    update_character_position(t_game *game, int new_x, int new_y)
{
    int     old_x;
    int     old_y;
    //char    new_tile;

    old_x = game->map->player.x;
    old_y = game->map->player.y;
    //new_tile = game->map->full[new_y][new_x];
    if (old_x != new_x || old_y != new_y)
    {
        clear_old_position(game, old_y, old_x);
        game->map->player.x = new_x;
        game->map->player.y = new_y;
        if (game->map->full[new_y][new_x] == COLLECTIBLE)
        {
            keep_score(game);
            game->map->full[new_y][new_x] = BACKGROUND;
            render_background(game, new_y, new_x);
        }
        if (game->map->full[new_y][new_x] == EXIT_OPEN)
            win_game(game);
        else
        {
            set_new_position(game, new_y, new_x);
            //render_static_map(game);
            render_player(game);
            count_moves(game);
        }
    }
    ft_printf("Old Position: x = %d, y = %d\n", old_x, old_y);
    ft_printf("Updated Position: x = %d, y = %d\n", new_x, new_y);
}


/*
void    update_character_position(t_game *game, int new_x, int new_y)
{
    int     old_x;
    int     old_y;
    char    old_tile;
    
    old_x = game->map->player.x;
    old_y = game->map->player.y;
    old_tile = game->map->full[old_y][old_x];
    if (old_x != new_x || old_y != new_y)
    {
        clear_old_position(game, old_y, old_x);
        game->map->player.x = new_x;
        game->map->player.y = new_y;
        if (old_tile == COLLECTIBLE)
        {
            keep_score(game);
            game->map->full[old_y][old_x] = BACKGROUND;
        }
        if (old_tile == BACKGROUND)
            game->map->full[old_y][old_x] = BACKGROUND;
        if (game->map->full[new_y][new_x] == EXIT_OPEN)
            win_game(game);
        else
            set_new_position(game, new_y, new_x);
        render_player(game);
        count_moves(game);
    }
    ft_printf("Old Position: x = %d, y = %d\n", old_x, old_y);
    ft_printf("Updated Position: x = %d, y = %d\n", new_x, new_y);
}
*/

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
                game->map->full[i][j] = BACKGROUND;
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
        ft_printf("You cannot go through walls!                     \n");
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
    
    if (game->move_cooldown > 0) //
    {
        game->move_cooldown--;  // Decrement cooldown and skip movement
        return;
    }
    
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
        if (new_x != game->map->player.x || new_y != game->map->player.y) {
            update_character_position(game, new_x, new_y);
            ft_printf("New player position: x = %d, y = %d\n", new_x, new_y);  // Debugging line
        }
    }
    game->move_cooldown = MOVE_DELAY;
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
    //find_character_position(game);
    render_static_map(game);
    //render_player(game);
    //game->map->full[game->map->player.y][game->map->player.y] = BACKGROUND; // change player position to background only after rendering player.
}

int main(int argc, char **argv)
{
    t_game  *game;

    check_args(argc, argv[1]);
    game = ft_calloc(1, sizeof(t_game));
    read_map(argv[1], game);
    print_map(game);
    load_images(game);
    initialise_game(game);
    start_game(game);
    mlx_loop_hook(game->mlx_ptr, ft_hook, game);
    mlx_loop(game->mlx_ptr);
    free_resources(game);
    return (0);
}
