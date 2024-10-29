/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:26:21 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/10/29 17:21:43 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	validate_argc(int argc)
{
	if (argc < 2)
	{
		ft_printf("Error\nAdd a map file.\n");
		exit(EXIT_FAILURE);
	}
	if (argc > 2)
	{
		ft_printf("Error\nToo many arguments.\n");
		exit(EXIT_FAILURE);
	}
}

static void	validate_file_name(char *map_file_name)
{
	size_t	len;

	len = ft_strlen(map_file_name);
	if (map_file_name[len - 4] != '.' || map_file_name[len - 3] != 'b'
		|| map_file_name[len - 2] != 'e' || map_file_name[len - 1] != 'r')
	{
		ft_printf("Error\nWrong file extension.\n");
		exit(EXIT_FAILURE);
	}
}

void	validate_args(int argc, char *map_file_name)
{
	validate_argc(argc);
	validate_file_name(map_file_name);
}
