/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:14:54 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/05/08 16:04:02 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*a;
	const unsigned char	*b;

	a = dst;
	b = src;
	if (dst == NULL && src == NULL)
		return (NULL);
	if (a < b)
	{
		while (len--)
		{
			*a++ = *b++;
		}
	}
	else
	{
		while (len--)
		{
			a[len] = b[len];
		}
	}
	return (dst);
}
/* The memmove() function copies len bytes from string 
src to string dst.  The two strings may overlap; the 
copy is always done in a non-destructive manner.
When the destination is larger than the source
bytes are copied from last to first. */