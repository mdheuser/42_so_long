/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:23:40 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/10/29 18:16:20 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_valid_chars(char tile)
{
	return (tile == 'P' || tile == 'E' || tile == 'C'
		|| tile == '1' || tile == '0' || tile == '\r');
}

static int	check_walls(t_game *game, char tile, int x, int y)
{
	if ((y == 0 || x == 0 || y == game->map_height - 1
			|| x == game->map_width -1)
		&& tile != '1')
		return (0);
	else
		return (1);
}

static int	check_tile(t_game *game, char tile)
{
	if (!check_valid_chars(tile))
		return (0);
	if (tile == 'P')
		(game->player_count)++;
	if (tile == 'E')
		(game->exit_count)++;
	if (tile == 'C')
		game->collectible_count++;
	return (1);
}

// Checks for valid characters (P E C 0 1),
// walls (the map should be completely enclosed),
// number of players (should be 1),
// number of exits (should be 1).
// collectibles (should be 1 or more),
// valid path (collectibles and exit should be accessible).
void	validate_map(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	if (!game || !game->map || !game->map->full)
		handle_error("Null pointer detected.", game);
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (game->map->full[y][x])
		{
			if (!check_tile(game, game->map->full[y][x]))
				handle_error("Invalid character detected.", game);
			if (!check_walls(game, game->map->full[y][x], x, y))
				handle_error("The map is not totally enclosed.", game);
			x++;
		}
		y++;
	}
	if (game->player_count != 1 || game->exit_count != 1
		|| game->collectible_count < 1)
		handle_error("Map validation failed.", game);
}
