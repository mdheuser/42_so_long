/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_motion2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:12:56 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/10/30 16:05:57 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Replaces collectibles (Pac-Men) with the background image
// when they are collected ("killed").
static void	check_collectibles(t_game *game, int new_y, int new_x)
{
	if (game->map->full[new_y][new_x] == COLLECTIBLE)
	{
		keep_score(game);
		game->map->full[new_y][new_x] = BACKGROUND;
		if (render_background(game, new_y, new_x) == -1)
			handle_error("Unable to render background.", game);
	}
}

// Updates player to a new position.
// This function also handles the case of winning the game.
void	update_player_position(t_game *game, int new_x, int new_y)
{
	int	old_x;
	int	old_y;

	old_x = game->map->player.x;
	old_y = game->map->player.y;
	if (old_x != new_x || old_y != new_y)
	{
		clear_old_position(game, old_y, old_x);
		game->map->player.x = new_x;
		game->map->player.y = new_y;
		check_collectibles(game, new_y, new_x);
		if (game->map->full[new_y][new_x] == EXIT_OPEN)
			win_game(game);
		else
		{
			set_new_position(game, new_y, new_x);
			if (render_player(game) == -1)
				handle_error("Unable to render the player image.", game);
			count_moves(game);
		}
	}
}

// Updates the exit image to "open" when all collectibles are collected
// (all Pac-Men are killed)
void	open_exit(t_game *game)
{
	int	exit_x;
	int	exit_y;

	exit_x = game->map->exit.x;
	exit_y = game->map->exit.y;
	game->map->full[exit_y][exit_x] = EXIT_OPEN;
	if (render_exit(game, exit_y, exit_x) == -1)
		handle_error("Unable to render exit image.", game);
}

void	clear_old_position(t_game *game, int old_y, int old_x)
{
	char	old_tile;

	old_tile = game->map->full[old_y][old_x];
	if (old_tile == BACKGROUND || old_tile == COLLECTIBLE)
	{		
		if (render_background(game, old_y, old_x) == -1)
			handle_error("Unable to render background image.", game);
	}
	else if (old_tile == EXIT || old_tile == EXIT_OPEN)
	{
		if (render_exit(game, old_y, old_x) == -1)
			handle_error("Unable to render exit image.", game);
	}
}

void	set_new_position(t_game *game, int new_y, int new_x)
{
	game->map->player.standing_on = game->map->full[new_y][new_x];
	game->map->player.x = new_x;
	game->map->player.y = new_y;
}
