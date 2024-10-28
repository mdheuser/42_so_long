/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_motion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:26:59 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/10/28 18:15:38 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	update_player_position(t_game *game, int new_x, int new_y)
{
	int	old_x;
	int	old_y;

	old_x = game->map->player.x;
	old_y = game->map->player.y;
	if (old_x != new_x || old_y != new_y)
	{
		clear_old_position(game, old_y, old_x);
		game->map->player.x = new_x;
		game->map->player.y = new_y;
		if (game->map->full[new_y][new_x] == COLLECTIBLE)
		{
			keep_score(game);
			game->map->full[new_y][new_x] = BACKGROUND;
			if (render_background(game, new_y, new_x) == -1)
			{
				cleanup_game(game);
				exit(1);
			}
		}
		if (game->map->full[new_y][new_x] == EXIT_OPEN)
			win_game(game);
		else
		{
			set_new_position(game, new_y, new_x);
			if (render_player(game) == -1)
			{
				cleanup_game(game);
				exit(1);
			}
			count_moves(game);
		}
	}
	//ft_printf("Old Position: x = %d, y = %d\n", old_x, old_y);
	//ft_printf("Updated Position: x = %d, y = %d\n", new_x, new_y);
}

int	can_move(t_game *game, int new_x, int new_y)
{
	if (new_y < 0 || new_y >= game->map_height || new_x < 0
		|| new_x >= game->map_width)
		return (0);
	else if (game->map->full[new_y][new_x] == WALL)
		return (0);
	return (1);
}

void	ft_hook(void *param)
{
	t_game	*game;
	int		new_x;
	int		new_y;

	game = (t_game *)param;
	new_x = game->map->player.x;
	new_y = game->map->player.y;
	if (game->move_cooldown > 0)
	{
		game->move_cooldown--;
		return ;
	}
	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx_ptr);
	else if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_UP)
		|| mlx_is_key_down(game->mlx_ptr, MLX_KEY_W))
		new_y -= 1;
	else if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_DOWN)
		|| mlx_is_key_down(game->mlx_ptr, MLX_KEY_S))
		new_y += 1;
	else if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_LEFT)
		|| mlx_is_key_down(game->mlx_ptr, MLX_KEY_A))
		new_x -= 1;
	else if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_RIGHT)
		|| mlx_is_key_down(game->mlx_ptr, MLX_KEY_D))
		new_x += 1;
	if (can_move(game, new_x, new_y)
		&& (new_x != game->map->player.x || new_y != game->map->player.y))
		update_player_position(game, new_x, new_y);
	game->move_cooldown = MOVE_DELAY;
}

void	manage_motion(t_game *game)
{
	mlx_loop_hook(game->mlx_ptr, ft_hook, game);
	mlx_loop(game->mlx_ptr);
}
