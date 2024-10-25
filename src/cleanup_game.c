/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 20:00:48 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/10/25 19:26:10 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
/*
void	free_double_p(char ***array)
{
	int	i;

	if (!array || !(*array))
		return ;
	i = 0;
	while ((*array)[i])
	{
		free((*array)[i]);  // Free each row
		i++;
	}
	free(*array);  // Free the array of pointers
	*array = NULL;  // Set the pointer to NULL for safety
}
*/

void	cleanup_game(t_game *game)
{
	int	i;

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
	i = 0;
	if (game->map)
    {
        if (game->map->full) // Check if full is not NULL
        {
            while (i < game->map_height) // Use map_height if known
            {
                free(game->map->full[i]);
				game->map->full[i] = NULL; // MAYBE NOT ??????????????????????????????
				i++;
			}
            free(game->map->full); // Free the array of pointers
			game->map->full = NULL;
        }
        free(game->map); // Free the map structure
		game->map = NULL;
	}
	free(game);
	game = NULL;
}
