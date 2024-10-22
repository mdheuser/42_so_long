/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_motion2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:12:56 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/10/22 15:15:38 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	open_exit(t_game *game)
{
	int	exit_x;
	int	exit_y;

	exit_x = game->map->exit.x;
	exit_y = game->map->exit.y;
	game->map->full[exit_y][exit_x] = EXIT_OPEN;
	render_exit(game, exit_y, exit_x);
}

void	clear_old_position(t_game *game, int old_y, int old_x)
{
	char	old_tile;

	old_tile = game->map->full[old_y][old_x];
	if (old_tile == BACKGROUND || old_tile == COLLECTIBLE)
		render_background(game, old_y, old_x);
	else if (old_tile == EXIT || old_tile == EXIT_OPEN)
		render_exit(game, old_y, old_x);
}

void	set_new_position(t_game *game, int new_y, int new_x)
{
	// Update what was under the player before moving
	game->map->player.standing_on = game->map->full[new_y][new_x];
	// Update player position
	game->map->player.x = new_x;
	game->map->player.y = new_y;
}
