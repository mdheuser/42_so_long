/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:58:48 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/10/29 17:28:35 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/////////////////// FOR DEBUGGING
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

	validate_args(argc, argv[1]);
	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		handle_error("Failed to allocate memory for game struct.", game);
	if (!initialise_game(game, argv[1]))
		handle_error("Failed to initialise game.", game);
	manage_motion(game);
	cleanup_game(game);
	exit(EXIT_SUCCESS);
}
