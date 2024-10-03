/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:23:00 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/05/08 12:25:45 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*result;
	size_t	bytes;

	bytes = size * count;
	if (size && count && (UINT_MAX / size < count))
		return (NULL);
	result = (void *)malloc(bytes);
	if (result == NULL)
		return (NULL);
	ft_bzero(result, bytes);
	return (result);
}
