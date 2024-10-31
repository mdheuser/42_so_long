/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:38:31 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/10/31 14:56:02 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "so_long.h"

// Counts how many Pac-Men were killed
void	keep_score(t_game *game)
{
	game->score--;
	if (game->score == 0)
	{
		open_exit(game);
		ft_printf("▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦\n");
		ft_printf("▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦ You've killed ALL Pac-Men! ▦▦▦▦▦▦▦▦▦▦▦▦▦\n");
		ft_printf("▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦ Well done! ▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦\n");
		ft_printf("▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦\n");
		ft_printf("▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦ The exit is now open. ▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦\n");
		ft_printf("▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦\n");
	}
	else if (game->score == 1)
	{
		ft_printf("▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦\n");
		ft_printf("▦▦▦▦▦▦▦▦▦▦▦▦▦▦ One Pac-Man left to kill! ▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦\n");
		ft_printf("▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦\n");
		ft_printf("▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦ KILL THEM ALL! ▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦\n");
		ft_printf("▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦\n");
	}
}

// Counts every movement from one tile to the next:
// Up, down, left, and right. No diagonal movements.
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
