/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:58:48 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/10/22 18:28:58 by mdahlstr         ###   ########.fr       */
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

	check_args(argc, argv[1]);
	game = ft_calloc(1, sizeof(t_game));
	read_map(argv[1], game);
	if (!validate_map(game))
	{
		ft_printf("Error\nInvalid map.\n");
		free_resources(game);
		exit(1);
	}
	load_images(game);
	initialise_game(game);
	render_static_map(game);
	manage_motion(game);
	free_resources(game);
	return (0);
}
