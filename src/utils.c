/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:38:31 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/10/29 18:55:57 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "so_long.h"

void	keep_score(t_game *game)
{
	game->score--;
	if (game->score == 0)
	{
		open_exit(game);
		ft_printf("\n\nYou've killed ALL Pac-Men!\nWell done!\n\n");
		ft_printf("~~~The exit is now open.~~~\n\n");
	}
	else if (game->score == 1)
		ft_printf("\n\nOne Pac-Man left to kill!\n~~~KILL THEM ALL!~~~\n\n");
}

void	count_moves(t_game *game)
{
	ft_printf("Moves: %d\n", game->move_count++);
}

// Prints error message, calls cleanup_game()
// and exits the programme (failure);
void	handle_error(const char *message, t_game *game)
{
	ft_printf("Error\n%s\n", message);
	if (game)
		cleanup_game(game);
	exit(EXIT_FAILURE);
}
