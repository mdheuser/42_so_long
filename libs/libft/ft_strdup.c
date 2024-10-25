/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:48:15 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/10/23 16:59:45 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* The strdup() function allocates sufficient memory 
for a copy of the string s1, does the copy, and returns
 a pointer to it.  The pointer may subsequently be used 
 as an argument to the function free(3).

If insufficient memory is available, NULL is returned
and errno is set to ENOMEM. */
char	*ft_strdup(const char *s1)
{
	char	*s1_copy;
	size_t	i;

	if (!s1)
		return (NULL);
	s1_copy = (char *)malloc(sizeof(*s1) * (ft_strlen(s1) + 1));
	if (!s1_copy)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s1_copy[i] = s1[i];
		i++;
	}	
	s1_copy[i] = '\0';
	return (s1_copy);
}
