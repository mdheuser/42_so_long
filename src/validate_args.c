/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:26:21 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/10/25 16:23:36 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	validate_argc(int argc)
{
	if (argc < 2)
	{
		ft_printf("Error\nInclude a map file in the format <maps/mapfile.ber>\n");
		return (0);
	}
	if (argc > 2)
	{
		ft_printf("Error\nToo many arguments\n");
		return (0);
	}
	return (1);
}

static int	validate_file_name(char *map_file_name)
{
	size_t	len;

	len = ft_strlen(map_file_name);
	if (map_file_name[len - 4] != '.' || map_file_name[len - 3] != 'b'
		|| map_file_name[len - 2] != 'e' || map_file_name[len - 1] != 'r')
	{
		ft_printf("Error\nWrong file extension\n");
		return (0);
	}
	return (1);
}

int	validate_args(int argc, char *map_file_name)
{
	if (!validate_argc(argc) || !validate_file_name(map_file_name))
		return (0);
	return (1);
}
