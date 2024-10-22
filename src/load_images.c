/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:13:44 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/10/22 15:28:16 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_textures(t_game *game)
{
	game->textures = ft_calloc(1, sizeof(t_textures));
	game->textures->background = mlx_load_png("imgs/bw_background.png");
	game->textures->wall = mlx_load_png("imgs/bw_walls2.png");
	game->textures->collectible = mlx_load_png("imgs/bw_pacman2.png");
	game->textures->player = mlx_load_png("imgs/bw_ghost2.png");
	game->textures->exit = mlx_load_png("imgs/bw_exit1.png");
	game->textures->exit_open = mlx_load_png("imgs/bw_exit2.png");
	if (!game->textures->background || !game->textures->wall
		|| !game->textures->collectible || !game->textures->player
		|| !game->textures->exit || !game->textures->exit_open)
	{
		ft_printf("Error\nError loading textures\n");
		return ;
	}
}

void	textures_to_image(t_game *game)
{
	game->images = ft_calloc(1, sizeof(t_images));
	game->images->background = mlx_texture_to_image(game->mlx_ptr,
			game->textures->background);
	game->images->wall = mlx_texture_to_image(game->mlx_ptr,
			game->textures->wall);
	game->images->collectible = mlx_texture_to_image(game->mlx_ptr,
			game->textures->collectible);
	game->images->player = mlx_texture_to_image(game->mlx_ptr,
			game->textures->player);
	game->images->exit = mlx_texture_to_image(game->mlx_ptr,
			game->textures->exit);
	game->images->exit_open = mlx_texture_to_image(game->mlx_ptr,
			game->textures->exit_open);
}

void	delete_textures(t_game *game)
{
	mlx_delete_texture(game->textures->background);
	mlx_delete_texture(game->textures->wall);
	mlx_delete_texture(game->textures->collectible);
	mlx_delete_texture(game->textures->player);
	mlx_delete_texture(game->textures->exit);
	mlx_delete_texture(game->textures->exit_open);
}

void	load_images(t_game *game)
{
	load_textures(game);
	textures_to_image(game);
	delete_textures(game);
}
