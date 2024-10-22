/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:47:29 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/10/22 13:59:43 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Measures the real width of the lines.
// Removes line breaks "\n" and carriage returns "\r"
size_t	find_width(char *line)
{
	size_t	line_len;

	line_len = ft_strlen(line);
	while (line_len > 0 && (line[line_len - 1] == '\n'
			|| line[line_len - 1] == '\r'))
		line_len--;
	return (line_len);
}

//Find map height and checks for inconsistency between line widths
size_t	find_height(int fd, char *line, size_t height, size_t *width)
{
	size_t	line_len;

	line = get_next_line(fd);
	while (line != NULL)
	{
		line_len = find_width(line);
		if (line_len != *width)
		{
			free(line);
			ft_printf("Error\nInconsistent map line widths.\n");
			exit(1);
		}
		height++;
		free(line);
		line = get_next_line(fd);
	}
	return (height);
}

size_t	get_map_dimensions(int fd, size_t *width)
{
	char	*line;
	size_t	height;
	size_t	line_len;

	line_len = 0;
	line = get_next_line(fd);
	if (!line)
		return (0);
	*width = find_width(line);
	if (*width == 0)
	{
		free(line);
		return (0);
	}
	height = 1;
	free(line);
	height = find_height(fd, line, height, width);
	//ft_printf("Map dimensions: height = %d, width = %d\n", height, *width);
	return (height);
}
