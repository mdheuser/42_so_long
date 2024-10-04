/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:39:53 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/10/04 16:39:15 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

#define WIDTH 768
#define HEIGHT 512

static mlx_image_t* image;
static mlx_texture_t *texture;

// -----------------------------------------------------------------------------

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		image->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		image->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		image->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		image->instances[0].x += 5;
}

// -----------------------------------------------------------------------------

int32_t main(int argc, char **argv)
{
	mlx_t* mlx;
	(void)argv;
	(void)argc;
	// Gotta error check this stuff
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "Duck Duck Go!", true)))
	{
		ft_printf("%s", mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	// Load PNG image as a texture
	texture = mlx_load_png("/home/mdahlstr/Documents/so_long_github/imgs/duck.png");
	if (!texture)
	{
		mlx_close_window(mlx);
		ft_printf("%s", mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	// Create an image with the same dimensions as the texture
	image = mlx_new_image(mlx, texture->width, texture->height);
	if (!image)
	{
		mlx_close_window(mlx);
		ft_printf("%s", mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	// Copy the texture data into the image
	if (!(image = mlx_texture_to_image(mlx, texture)))
	{
    	ft_printf("Error: Could not copy texture to image");
    	mlx_close_window(mlx);
    	return(EXIT_FAILURE);
	}
	mlx_image_to_window(mlx, image, 0, 0);
	// Set up the hooks for key movements
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);	
	return (EXIT_SUCCESS);
}
