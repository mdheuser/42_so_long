/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:48:15 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/04/29 13:15:33 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s1_copy;
	size_t	len;

	len = ft_strlen(s1);
	s1_copy = malloc(sizeof(char) * len + 1);
	if (!s1_copy)
		return (0);
	s1_copy = ft_memcpy(s1_copy, s1, len);
	s1_copy[len] = '\0';
	return (s1_copy);
}
/* The strdup() function allocates sufficient memory 
for a copy of the string s1, does the copy, and returns
 a pointer to it.  The pointer may subsequently be used 
 as an argument to the function free(3).

If insufficient memory is available, NULL is returned
and errno is set to ENOMEM. */
