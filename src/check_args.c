/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:26:21 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/10/21 18:56:00 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void    check_argc(int argc)
{
    if (argc < 2)
    {
        ft_printf("Error\nInclude a map file in the format <maps/mapfile.ber>\n");
        exit(1);
    }
    if (argc > 2)
    {
        ft_printf("Error\nToo many arguments\n");
        exit(1);
    }
}

void    check_file_name(char *map_file_name)
{
    size_t  len;

    len = ft_strlen(map_file_name);
    if (map_file_name[len - 4] != '.' || map_file_name[len - 3] != 'b'
    || map_file_name[len - 2] != 'e' || map_file_name[len - 1] != 'r')
    {
        ft_printf("Error\nWrong file extension\n");
        exit(1);
    }
}

void	check_args(int argc, char *map_file_name)
{
    check_argc(argc);
    check_file_name(map_file_name);
}
