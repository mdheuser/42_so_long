/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:45:47 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/08/28 16:15:23 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_hex(unsigned long int n, char specifier)
{
	int	count;

	count = 0;
	if (n >= 16)
	{
		count += print_hex((n / 16), specifier);
		if (count == -1)
			return (-1);
		count += print_hex((n % 16), specifier);
	}
	else
	{
		if (specifier == 'x')
			count = print_char("0123456789abcdef"[n]);
		else
			count = print_char("0123456789ABCDEF"[n]);
		if (count == -1)
			return (-1);
		return (count);
	}
	return (count);
}
