/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:51:27 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/10/02 15:07:36 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*reset_and_rtrn_null(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
	return (NULL);
}

static char	*create_stash(int fd, char *stash, char *buffer)
{
	char		*tmp;
	ssize_t		bytes_read;

	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(stash, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (reset_and_rtrn_null(&stash));
		else if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		tmp = ft_strjoin(stash, buffer);
		if (!tmp)
		{
			free(stash);
			stash = NULL;
			return (reset_and_rtrn_null(&buffer));
		}
		free(stash);
		stash = NULL;
		stash = tmp;
	}
	return (stash);
}

static char	*extract_line(char *str)
{
	char	*line;
	size_t	line_len;
	size_t	i;

	line_len = 0;
	while (str[line_len] != '\n' && str[line_len] != '\0')
		line_len++;
	if (str[line_len] == '\n')
		line_len++;
	line = (char *)malloc((line_len + 1) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (i < line_len)
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*remove_line(char *stash, char *line_to_remove)
{
	size_t	len_stash;
	size_t	len_line;
	char	*tmp;

	len_line = ft_strlen(line_to_remove);
	len_stash = ft_strlen(stash);
	if (len_line < len_stash)
	{
		tmp = ft_substr(stash, len_line, len_stash - len_line);
		free(stash);
		stash = NULL;
		if (!tmp)
			return (NULL);
		stash = tmp;
	}
	else
		return (reset_and_rtrn_null(&stash));
	return (stash);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*pre_line;
	char		*line;

	if (!pre_line)
		pre_line = ft_strdup("");
	if (!pre_line)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (reset_and_rtrn_null(&pre_line));
	buffer = (char *)malloc((BUFFER_SIZE + 1) * (sizeof(char)));
	if (!buffer)
		return (reset_and_rtrn_null(&pre_line));
	pre_line = create_stash(fd, pre_line, buffer);
	if (!pre_line)
		return (NULL);
	free(buffer);
	buffer = NULL;
	if (pre_line && pre_line[0] == '\0')
		return (reset_and_rtrn_null(&pre_line));
	line = extract_line(pre_line);
	if (!line)
		return (reset_and_rtrn_null(&pre_line));
	pre_line = remove_line(pre_line, line);
	return (line);
}
