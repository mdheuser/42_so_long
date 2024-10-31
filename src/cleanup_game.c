/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 20:00:48 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/10/31 12:57:03 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Frees the 2d array that makes up the map.
static void	free_map(t_game *game)
{
	int	i;

	i = 0;
	if (game->map)
	{
		if (game->map->full)
		{	
			while (i < game->map_height)
			{
				if (game->map->full[i])
				{
					free(game->map->full[i]);
					game->map->full[i] = NULL;
				}
				i++;
			}
			free(game->map->full);
			game->map->full = NULL;
		}
		free(game->map);
		game->map = NULL;
	}
}

// Frees all memory that is still allocated up to this point.
void	cleanup_game(t_game *game)
{
	if (!game)
		return ;
	if (game->textures)
	{
		free_textures(game);
		game->textures = NULL;
	}
	if (game->images)
	{
		free_images(game);
		game->images = NULL;
	}
	if (game->mlx_ptr)
	{
		mlx_terminate(game->mlx_ptr);
		game->mlx_ptr = NULL;
	}
	free_map(game);
	free(game);
}
