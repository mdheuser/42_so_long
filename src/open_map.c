/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:31:51 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/10/10 16:13:40 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*Some of the allowed functions:

open, close, read, write,
malloc, free, perror,
strerror, exit

*/

void    parse_map();
/* The map must contain 1 exit, at least 1 collectible, and 1 starting position to be valid.
--- If the map contains a duplicates characters (exit/start), you should
display an error message
 --- The map must be rectangular. (if any line is longer or shorter than another: ERROR)
• --- The map must be closed/surrounded by walls. If it’s not, the program must return
an error. (ALL X 0 and X N must be '1' // ALL Y 0 and Y N must be 1)
• You have to check if there’s a valid path in the map. 
• You must be able to parse any kind of map, as long as it respects the above rules.
*/


char **load_map(const char *file_path)
{
    int fd;
    
    fd = open(file_path, O_RDONLY);
    
    // Open the file, read each line, and store it in a 2D array
    // Implement logic to dynamically allocate and read the file
    // For simplicity, you can assume that each line has the same number of characters (width)
    // and that the map is rectangular.
}