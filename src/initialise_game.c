/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_game.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:22:01 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/10/25 17:09:30 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// ATTENTION! This function also turns the initial player position into a background tile!
int	find_player_position(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if (game->map->full[i][j] == PLAYER)
			{
				game->map->player.x = j;
				game->map->player.y = i;
				game->map->full[i][j] = BACKGROUND;
				//ft_printf("Initial character position: x = %d, y = %d\n", game->map->player.x, game->map->player.y);
				return (1);
			}
			j++;
		}
		i++;
	}
	ft_printf("Error\nPlayer not found in the map.\n");
	return (0);
}

int	initialise_game(t_game *game, char *map_name)
{
	game->mlx_ptr = NULL;
	game->map = NULL;
	game->textures = NULL;
	game->images = NULL;
	if (!read_map(map_name, game))
	{	
		ft_printf("Error\nFailed to read map file.\n");
		return (0);
	}
	if (!validate_map(game))
		return (0);
	if (!find_player_position(game))
		return (0);
	if (!load_images(game))
		return (0);
	if (render_static_map(game) == -1)
		return (0);
	if (render_player(game) == -1)
		return (0);
	game->score = game->collectible_count;
	game->move_count = 1;
	return (1);
}
