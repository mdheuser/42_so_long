/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:58:48 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/10/28 19:06:42 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/////////////////// TEMPORARY DEBUGGING
/*
void print_map(t_game *game)
{
	int y = 0;
	while (y < game->map_height)
	{
		ft_printf("%s\n", game->map->full[y]);
		y++;
	}
}
*/
int	main(int argc, char **argv)
{
	t_game	*game;

	ft_printf("running main...\n");
	if (!validate_args(argc, argv[1]))
		return (1);
	ft_printf("checked arguments\n");
	game = ft_calloc(1, sizeof(t_game));
	if (!game)
	{
		ft_printf("Error\nFailed to allocate memory for game struct.\n");
		return (1);
	}
	ft_printf("allocated memory for game\n");
	if (!initialise_game(game, argv[1]))
	{
		ft_printf("Error\nFailed to initialise game.");
		cleanup_game(game);
		return (1);
	}
	manage_motion(game);
	cleanup_game(game);
	return (EXIT_SUCCESS);
}
