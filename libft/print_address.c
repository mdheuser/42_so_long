/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_address.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:48:50 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/08/28 16:15:10 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_address(unsigned long int ptr)
{
	int	count;

	count = 0;
	if (!ptr)
	{
		count = write(1, "0x0", 3);
		return (count);
	}
	else
	{
		count += write(1, "0x", 2);
		if (count == -1)
			return (-1);
		count += print_hex(ptr, 'x');
		if (count == -1)
			return (-1);
		return (count);
	}
	return (count);
}
