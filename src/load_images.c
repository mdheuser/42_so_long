/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:13:44 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/10/28 18:03:49 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


void free_textures(t_game *game)
{
	if (!game || !game->textures) // Check if game or textures is NULL
        return ;
    if (game->textures->background)
        mlx_delete_texture(game->textures->background);
    if (game->textures->wall)
        mlx_delete_texture(game->textures->wall);
    if (game->textures->collectible)
        mlx_delete_texture(game->textures->collectible);
    if (game->textures->player)
        mlx_delete_texture(game->textures->player);
    if (game->textures->exit)
        mlx_delete_texture(game->textures->exit);
    if (game->textures->exit_open)
        mlx_delete_texture(game->textures->exit_open);
    free(game->textures);  // Free the textures struct itself
    game->textures = NULL;
}

void free_images(t_game *game)
{
	if (!game || !game->images) // Check if game or images is NULL
        return ;
    if (game->images->background)
        mlx_delete_image(game->mlx_ptr, game->images->background);
    if (game->images->wall)
        mlx_delete_image(game->mlx_ptr, game->images->wall);
    if (game->images->collectible)
        mlx_delete_image(game->mlx_ptr, game->images->collectible);
    if (game->images->player)
        mlx_delete_image(game->mlx_ptr, game->images->player);
    if (game->images->exit)
        mlx_delete_image(game->mlx_ptr, game->images->exit);
    if (game->images->exit_open)
        mlx_delete_image(game->mlx_ptr, game->images->exit_open);
    free(game->images);  // Finally, free the images struct
    game->images = NULL;
}

static int	load_textures(t_game *game)
{
	game->textures = ft_calloc(1, sizeof(t_textures));
	if (!game->textures)
        return (0);  // Allocation failure
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
		ft_printf("Error\nFailed to load textures\n");
		free_textures(game);
		return (0);
	}
	return (1);
}

static int	textures_to_image(t_game *game)
{
	game->images = ft_calloc(1, sizeof(t_images));
	if (!game->images)
        return (0);  // Allocation failure
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
	if (!game->images->background || !game->images->wall
		|| !game->images->collectible || !game->images->player
		|| !game->images->exit || !game->images->exit_open)
	{
		ft_printf("Error\nFailed to turn textures into images\n");
		free_images(game);
		return (0);
	}
	return (1);
}

static void	delete_textures(t_game *game)
{
	mlx_delete_texture(game->textures->background);
	mlx_delete_texture(game->textures->wall);
	mlx_delete_texture(game->textures->collectible);
	mlx_delete_texture(game->textures->player);
	mlx_delete_texture(game->textures->exit);
	mlx_delete_texture(game->textures->exit_open);
}

int	load_images(t_game *game)
{
	if (!load_textures(game) || !textures_to_image(game))
	{
		ft_printf("Error\nFailed to load textures or images.\n");
		return (0);
	}
	delete_textures(game);
	ft_printf("Images and Textures loaded.\n");
	return (1);
}
