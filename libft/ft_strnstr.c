/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:16:48 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/04/29 13:14:49 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	needle_len;
	char	*h;

	h = (char *) haystack;
	needle_len = ft_strlen(needle);
	if (needle_len == 0 || haystack == needle)
		return (h);
	i = 0;
	while (h[i] != '\0' && i < len)
	{
		j = 0;
		while (h[i + j] != '\0' && needle[j] != '\0'
			&& h[i + j] == needle[j] && (i + j < len))
		{
			j++;
		}
		if (j == needle_len)
			return (h + i);
		i++;
	}
	return (0);
}
/* The strnstr() function locates the first occurrence
 of the null-terminated string needle in the string
 haystack, where not more than len characters are searched.
 Characters that appear after a `\0' character are 
 not searched.  Since the strnstr() function is a
 FreeBSD specific API, it should only be used when
 portability is not a concern.
	 
 RETURN VALUES
 If needle is an empty string, haystack is returned;
 if needle occurs nowhere in haystack, NULL is returned;
 otherwise a pointer to the first character of the first
 occurrence of needle is returned. */