/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:47:58 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/10/02 15:39:01 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last;

	last = (char *)s + ft_strlen(s);
	while (last > s && *last != (char)c)
		last--;
	if (*last == (char)c)
		return (last);
	return (NULL);
}
/* DESCRIPTION
     The strrchr() function locates the last occurrence
	 of c (converted to a char) in the string pointed to
	 by s.  The terminating null character is considered
	 to be part of the string; therefore if c is `\0',
	 the function locates the terminating `\0'.

RETURN VALUES
     The strrchr() function returns a pointer to the
	 located character, or NULL if the character does
	 not appear in the string. */