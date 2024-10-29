/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_game.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:22:01 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/10/29 16:12:00 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	initialise_vars(t_game *game)
{
	game->mlx_ptr = NULL;
	game->map = NULL;
	game->textures = NULL;
	game->images = NULL;
	game->map_width = 0;
	game->map_height = 0;
	game->score = 0;
	game->collectible_count = 0;
	game->move_count = 0;
	game->move_cooldown = 0;
	game->exit_flag = 0;
}

int	init_mlx_window(t_game *game)
{
	game->mlx_ptr = mlx_init((game->map_width) * TILESIZE, game->map_height
			* TILESIZE, "~~~~~~ Pac-Ghost ~~~~~~", false);
	if (!game->mlx_ptr)
	{
		cleanup_game(game);
		game->mlx_ptr = NULL;
		return (0);
	}
	return (1);
}

// ATTENTION! This function also turns the initial 
// player position into a background tile!
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
				ft_printf("Initial character position: x = %d, y = %d\n",
					game->map->player.x, game->map->player.y);
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
	initialise_vars(game);
	if (!read_map(map_name, game))
		return (0);
	if (!validate_map(game))
		return (0);
	if (!validate_path(game))
		return (0);
	if (!find_player_position(game))
		return (0);
	if (!init_mlx_window(game))
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
