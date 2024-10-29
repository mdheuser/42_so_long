/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:31:35 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/10/29 18:52:16 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	restore_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (game->map->full[y][x])
		{
			if (game->map->full[y][x] == 'e')
				game->map->full[y][x] = EXIT;
			else if (game->map->full[y][x] == 'c')
				game->map->full[y][x] = COLLECTIBLE;
			else if (game->map->full[y][x] == 'o')
				game->map->full[y][x] = BACKGROUND;
			x++;
		}
		y++;
	}
}

static bool	update_tile(t_game *game, int y, int x, int *c_count)
{
	if (game->map->full[y][x] == 'E')
	{
		game->exit_flag = 1;
		game->map->full[y][x] = 'e';
		if (*c_count == 0)
			return (false);
	}
	else if (game->map->full[y][x] == 'C')
	{
		(*c_count)--;
		game->map->full[y][x] = 'c';
		if (*c_count == 0 && game->exit_flag)
			return (false);
	}
	else if (game->map->full[y][x] == '0')
		game->map->full[y][x] = 'o';
	return (true);
}

static bool	ft_floodfill(t_game *game, int y, int x, int *c_count)
{
	if (x < 0 || x >= game->map_width || y < 0 || y >= game->map_height)
		return (true);
	if (game->map->full[y][x] == '1' || game->map->full[y][x] == 'c'
		|| game->map->full[y][x] == 'o' || game->map->full[y][x] == 'e')
		return (true);
	if (!update_tile(game, y, x, c_count))
		return (false);
	if (ft_floodfill(game, (y - 1), x, c_count)
		&& ft_floodfill(game, (y + 1), x, c_count)
		&& ft_floodfill(game, y, (x - 1), c_count)
		&& ft_floodfill(game, y, (x + 1), c_count))
		return (true);
	return (false);
}

// This function uses the same full 2d map to verify if the path is valid,
// that is, if exits and collectibles can all be reached.
// All background, collectibles and exit tiles
// are replaced with corresponding characters:
// E -> e C -> c, 0 -> o.
// The map is then restored to its original characters.
void	validate_path(t_game *game)
{
	int	x;
	int	y;
	int	c_count;

	y = 0;
	c_count = game->collectible_count;
	while (y < game->map_height)
	{
		x = 0;
		while (game->map->full[y][x])
		{
			if (game->map->full[y][x] == PLAYER)
			{
				ft_floodfill(game, y, x, &c_count);
				if (c_count != 0)
					handle_error("One or more Pac-Men inaccessible.", game);
				if (game->exit_flag == 0)
					handle_error("The Exit is not accessible!", game);
				restore_map(game);
			}
			x++;
		}
		y++;
	}
}
