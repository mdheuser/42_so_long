/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_static_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:08:58 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/10/29 18:54:15 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	render_tile(t_game *game, char tile, int y, int x)
{
	if (tile == WALL)
	{
		if (render_walls(game, y, x) == -1)
			handle_error("Unable to render  walls.", game);
	}
	else if (tile == COLLECTIBLE)
	{
		if (render_collectibles(game, y, x) == -1)
			handle_error("Unable to render Pac-Men", game);
	}
	else if (tile == EXIT || tile == EXIT_OPEN)
	{
		if (render_exit(game, y, x) == -1)
			handle_error("Unable to render the exit", game);
	}
}

// Covers entire window with background image
static void	cover_background(t_game *game)
{
	int		x;
	int		y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (render_background(game, y, x) == -1)
				handle_error("Unable to render background.", game);
			x++;
		}
		y++;
	}
}

void	render_static_map(t_game *game)
{
	int		x;
	int		y;
	char	tile;

	cover_background(game);
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			tile = game->map->full[y][x];
			render_tile(game, tile, y, x);
			x++;
		}
		y++;
	}
}
