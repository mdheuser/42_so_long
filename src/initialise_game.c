/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_game.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:22:01 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/10/22 17:14:55 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// ATTENTION! This function also turns the initial player position into a background tile!
void	find_player_position(t_game *game)
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
				return ;
			}
			j++;
		}
		i++;
	}
	ft_printf("Player not found in the map.\n");
}

void	initialise_game(t_game *game)
{
	find_player_position(game);
	render_player(game);
	game->score = game->collectible_count;
	game->move_count = 1;
}
