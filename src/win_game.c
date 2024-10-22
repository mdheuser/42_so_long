/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:44:02 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/10/22 15:19:01 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	win_game(t_game *game)
{
	if (game->score == 0)
	{
		count_moves(game);
		ft_printf("\n\nGood ghost!\nYou've finished the game with %d moves.\n",
			game->move_count);
		ft_printf("Can you do it in fewer?\n");
		exit(EXIT_SUCCESS);
	}
}
