/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:46:49 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/08/28 16:15:34 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_unsigned(unsigned int n)
{
	int						bytes_printed;
	unsigned long long int	number;

	bytes_printed = 0;
	number = n;
	if (number >= 10)
	{
		bytes_printed += print_unsigned(number / 10);
		if (bytes_printed == -1)
			return (-1);
		bytes_printed += print_unsigned(number % 10);
	}
	else
		bytes_printed += print_char(number + '0');
	return (bytes_printed);
}
