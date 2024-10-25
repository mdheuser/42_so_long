/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_memory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:40:52 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/10/23 17:47:01 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Important: map lines are alocated with get_next_line and freed immediately in read_map() 
void    malloc_all(t_game *game)
{
	//game = ft_calloc(1, sizeof(t_game));
	game->images = ft_calloc(1, sizeof(t_images));

}

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

void	free_all(t_game *game)
{
	int	i;

	i = 0;
	while (game->map->full[i] != NULL)
	{
		free(game->map->full[i]);
		i++;
	}
	
	// Free other allocated structures
    free(game->textures);
    free(game->images);

	free(game->map->full);
	free(game);
	mlx_terminate(game->mlx_ptr);
}
