/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:44:02 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/10/31 20:01:57 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Handles successful completion of the game:
// Condition: all collectibles are collected and
// the open exit was reached.
// Frees allocated memory and exits the programme with no error.
void	win_game(t_game *game)
{
	if (game->score == 0)
	{
		count_moves(game);
		ft_printf("▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦\n");
		ft_printf("▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦ YOU WIN! ▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦\n");
		ft_printf("▦▦▦▦▦▦▦▦▦▦▦ Your total number of moves is %d. ▦▦▦▦▦▦▦▦▦▦\n",
			game->move_count);
		ft_printf("▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦\n");
		ft_printf("▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦ Can you do it in fewer? ▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦\n");
		ft_printf("▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦\n");
		cleanup_game(game);
		exit(EXIT_SUCCESS);
	}
}
