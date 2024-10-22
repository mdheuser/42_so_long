/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_static_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:08:58 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/10/22 14:13:48 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Covers entire window with background image
void	cover_background(t_game *game)
{
	int		x;
	int		y;

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
