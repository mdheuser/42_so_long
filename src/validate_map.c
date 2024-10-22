/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:23:40 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/10/22 18:32:40 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_valid_chars(char tile)
{
	return (tile == 'P' || tile == 'E' || tile == 'C'
		|| tile == '1' || tile == '0');
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
/*
static void fill_visited(char ***visited, t_game *game)
{
	int i;
	int j;

	i = 0;
	while (game->map->full[i])
	{
		j = 0;
		(*visited)[i] = malloc(sizeof(char) * (game->map_width + 1)); // Allocate memory for each row
		if (!(*visited)[i])
		{
    	// Handle memory allocation failure
    		while (i > 0)
			{
        		free((*visited)[--i]);
    		}
    		free(*visited);
    		ft_printf("Error\nMemory allocation failed for visited row.\n");
    		return;
		}
		while (game->map->full[i][j])
		{
			(*visited)[i][j] = game->map->full[i][j]; // Initialize visited array with the map values
			j++;
		}
		(*visited)[i][j] = '\0'; // Null-terminate each row
		i++;
	}
}*/

// This is the same as a FLOOD_FILL function.
int	find_path(t_game *game, int x, int y, char **visited, char target)
{
	int	up;
	int	down;
	int	left;
	int	right;

	if (x < 0 || y < 0 || x >= game->map_width || y >= game->map_height
	|| visited[y][x] == '1' || game->map->full[y][x] == '1')
		return (0);
	if (game->map->full[y][x] == target)
		return (1);
	visited[y][x] = '1';
	up = find_path(game, x, y - 1, visited, target);
	down = find_path(game, x, y + 1, visited, target);
	left = find_path(game, x - 1, y, visited, target);
	right = find_path(game, x + 1, y, visited, target);
	if (up || down || left || right)
		return (1);
	return (0);
}

int	validate_map(t_game *game)
{
	int 	x;
	int 	y;
	int		player_count;
	int		exit_count;
	char	tile;
	//char	**visited;
	
	x = 0;
	y = 0;
	player_count = 0;
	exit_count = 0;
	
	while (game->map->full[y])
	{
		x = 0;
		while (game->map->full[y][x])
		{
			tile = game->map->full[y][x];
			if (!check_valid_chars(tile))
			{	
				ft_printf("Error\ninvalid chars\n");
				return (0);
			}
			if (!check_walls(game, tile, x, y))
			{
				//ft_printf("x = %d, y = %d\n", x, y);
				ft_printf("Error\nMap not entirely enclosed by walls. %d\n", check_walls(game, tile, x, y));
				return (0);
			}
			if (tile == 'P')
				player_count++;
			if (tile == 'E')
				exit_count++;
			if (tile == 'C')
				game->collectible_count++;
			x++;
		}
		y++;
	}
	if (player_count != 1 || exit_count != 1 || game->collectible_count < 1)
	{	
		ft_printf("Error\nSomething missing from your map!\n (player, exit, or pacman) too many or too few ;-)\n");
		return (0);
	}
	/*
	visited = malloc(sizeof(char *) * (game->map_height + 1));
	visited[game->map_height] = NULL; // Null-terminate the array of pointers
	if (!visited)
	{
		ft_printf("Error\nMemory allocation failed for visited.\n");
		return (0);
	}
	fill_visited(&visited, game);
	if  (!find_path(game, game->map->player.x, game->map->player.y, visited,'C'))
	{
		free_double_p(&visited);
		return (0);
	}
	fill_visited(&visited, game);
	if  (!find_path(game, game->map->player.x, game->map->player.y, visited, 'E'))
	{
		free_double_p(&visited);
		return (0);
	}
	free_double_p(&visited);
	ft_printf("Map validated!\n");
	*/
	return (1);
}
