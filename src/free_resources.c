/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 20:00:48 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/10/22 18:13:52 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

void	free_resources(t_game *game)
{
	int	i;

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
