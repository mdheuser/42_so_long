/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 20:00:48 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/10/21 20:01:01 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void    free_resources(t_game *game)
{   
    int i;

    i = 0;
    while (game->map->full[i] != NULL)
    {
        free(game->map->full[i]);
        i++;
    }
    free(game->map->full);
    free(game);
    mlx_terminate(game->mlx_ptr);
}