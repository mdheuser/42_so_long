/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:31:35 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/10/28 20:53:20 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


int ft_floodfill(t_game game, int y, int x)
{
    
    return (0); // in case of error    
}


restore_map(game);

// Uses the same full 2d map to verify if the path is valid,
// that is, if exits and collectibles can all be reached.
// all background, collectibles and exit tiles
// are replaced with corresponding characters:
// E -> e C -> c, 0 -> o.
// Once the map is validated, it is restored to its 
// original characters.
int validate_path(t_game *game)
{
    int x;
    int y;

    y = 0;
    ft_printf("Checking map path...\n");
    while (y < game->map_height)
	{
		x = 0;
		while (game->map->full[y][x])
		{
		    if (game->map->full[y][x] == PLAYER)
            {
                ft_floodfill(game, y, x);
                restore_map(game);
            }
            x++;
        }
    }
    return (1);
}