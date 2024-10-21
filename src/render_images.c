/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_images.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:35:59 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/10/21 19:37:16 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

void    render_static_map(t_game *game)
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