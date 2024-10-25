/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_static_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:08:58 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/10/25 17:05:34 by mdahlstr         ###   ########.fr       */
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

int	render_static_map(t_game *game)
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
			{
				if (render_walls(game, y, x) == -1)
					return (-1);
			}
			else if (tile == COLLECTIBLE)
			{
				if (render_collectibles(game, y, x) == -1)
					return (-1);
			}
			else if (tile == EXIT || tile == EXIT_OPEN)
			{
				if (render_exit(game, y, x) == -1)
					return (-1);
			}
			x++;
		}
		y++;
	}
	//if (render_player(game) == -1)
	//	return (-1);
	return (1);
}
