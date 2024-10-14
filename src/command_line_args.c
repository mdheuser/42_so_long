/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line_args.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:11:51 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/10/10 14:39:46 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void    close_game(t_game *game)
{
    
}

void    parse_command_line_args(int argc, char  **argv, t_game *game)
{
    size_t  map_name_len;

    // set map allocation to false. Why?

     // check if argc > 2 : too many args
    if (argc > 2)
    {
        ft_printf("Too many arguments. Only enter the name of the executable followed map location.");
        close_game(game);
    }
     // check if argc == 1 : no args
    if (argc < 2)
    {
        ft_printf("Enter map file location.");
        close_game(game);
    }
    map_name_len = ft_strlen(argv[1]);
    if (map_name_len > 4 && ft_strncmp(&argv[1][map_name_len - 4], ".ber", 4) == 0)
    {
        ft_printf("Map extension is not .ber");
        close_game(game);
    }
    // check if map is .ber.
}