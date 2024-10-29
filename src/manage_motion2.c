/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_motion2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:12:56 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/10/29 17:32:07 by mdahlstr         ###   ########.fr       */
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
