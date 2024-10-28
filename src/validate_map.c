/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:23:40 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/10/28 20:31:05 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_valid_chars(char tile)
{
	return (tile == 'P' || tile == 'E' || tile == 'C'
		|| tile == '1' || tile == '0' || tile == '\r');
}

int	check_walls(t_game *game, char tile, int x, int y)
{
	//ft_printf("map width: %d, map height %d\n", game->map_width, game->map_height);
	if ((y == 0 || x == 0 || y == game->map_height - 1 || x == game->map_width -1)
		&& tile != '1')
		return (0);
	else
		return (1);
}

// Checks for valid characters (P E C 0 1),
// walls (the map should be completely enclosed),
// number of players (should be 1),
// number of exits (should be 1).
// collectibles (should be 1 or more),
// valid path (collectibles and exit should be accessible).
int	validate_map(t_game *game)
{
	int 	x;
	int 	y;
	int		player_count;
	int		exit_count;
	char	tile;
	// char	**visited;

	x = 0;
	y = 0;
	player_count = 0;
	exit_count = 0;
	
	if (!game || !game->map || !game->map->full) 
	{
    	ft_printf("Error: Null pointer detected!\n");
    	return (0);
	}
	ft_printf("Map validation started...\n");
	if (!game->map->full)
	{
		ft_printf("Error\nMap is not initialized!\n");
		return (0);
	}
	printf("Map height (right before loop to check map): %d\n", game->map_height);
	while (y < game->map_height)
	{
		ft_printf("Checking row %d...\n", y); // Print current row
		x = 0;
		while (game->map->full[y][x])
		{
			tile = game->map->full[y][x];
			ft_printf("Checking tile at position (%d, %d): '%c'\n", x, y, tile); // Print each tile

			// Check for valid characters
			if (!check_valid_chars(tile))
			{
				ft_printf("Error\nInvalid character detected at (%d, %d): '%c'\n", x, y, tile);
				return (0);
			}

			// Check if the walls are correct
			if (!check_walls(game, tile, x, y))
			{
				ft_printf("Error\nMap not enclosed by walls at (%d, %d): '%c'\n", x, y, tile);
				return (0);
			}
			// Count players, exits, and collectibles
			if (tile == 'P')
			{
				player_count++;
				ft_printf("Player found at (%d, %d)\n", x, y);
			}
			if (tile == 'E')
			{
				exit_count++;
				ft_printf("Exit found at (%d, %d)\n", x, y);
			}
			if (tile == 'C')
			{
				game->collectible_count++;
				ft_printf("Collectible found at (%d, %d)\n", x, y);
			}
			x++;
		}
		y++;
	}
	// Validate the number of players, exits, and collectibles
	if (player_count != 1 || exit_count != 1 || game->collectible_count < 1)
	{
		ft_printf("Error\nMap validation failed: incorrect number of players, exits, or collectibles.\n");
		return (0);
	}
	ft_printf("Map validated successfully!\n");
	return (1);
}

