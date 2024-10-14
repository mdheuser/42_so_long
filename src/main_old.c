/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:39:53 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/10/10 14:46:16 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

#define WIDTH 768
#define HEIGHT 512

static mlx_image_t *ghost_img;
static mlx_image_t *background_img;
static mlx_texture_t *ghost_texture;
static mlx_texture_t *background_texture;

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
		ghost_img->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		ghost_img->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		ghost_img->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		ghost_img->instances[0].x += 5;
}

// -----------------------------------------------------------------------------

int32_t main(int argc, char **argv)
{
	mlx_t* mlx;
	(void)argv;
	(void)argc;
	t_game	*game;

	game = malloc(sizeof(t_game));
	parse_command_line_args(argc, argv, game);
	game.map = load_map(argv[1]);
	
	// Gotta error check this stuff
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "Pac-Ghost", true)))
	{
		ft_printf("%s", mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	// Load PNG image as a texture
	ghost_texture = mlx_load_png("./imgs/ghost.png");
	if (!ghost_texture)
	{
		mlx_close_window(mlx);
		ft_printf("%s", mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	background_texture = mlx_load_png("./imgs/background.png");
	if (!background_texture)
	{
		mlx_close_window(mlx);
		ft_printf("%s", mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	// Create an image with the same dimensions as the texture
	ghost_img = mlx_new_image(mlx, ghost_texture->width, ghost_texture->height);
	if (!ghost_img)
	{
		mlx_close_window(mlx);
		ft_printf("%s", mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	// Copy the texture data into the image
	if (!(ghost_img = mlx_texture_to_image(mlx, ghost_texture)))
	{
    	ft_printf("Error: Could not copy texture to image");
    	mlx_close_window(mlx);
    	return(EXIT_FAILURE);
	}
	mlx_image_to_window(mlx, ghost_img, 0, 0);
	mlx_image_to_window(mlx, background_img, 0, 0);
	// Set up the hooks for key movements
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);	
	return (EXIT_SUCCESS);
}

/*
typedef struct mlx_texture
{
	uint32_t	width;
	uint32_t	height;
	uint8_t		bytes_per_pixel;
	uint8_t*	pixels;
}	mlx_texture_t;

*/

/*
 * Main MLX handle, carries important data in regards to the program.
 * @param window The window itself.
 * @param context Abstracted opengl data.
 * @param width The width of the window.
 * @param height The height of the window.
 * @param delta_time The time difference between the previous frame 
 * and the current frame.
 */
/*
typedef struct mlx
{
	void*		window;
	void*		context;
	int32_t		width;
	int32_t		height;
	double		delta_time;
}	mlx_t;
*/