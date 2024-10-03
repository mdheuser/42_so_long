/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:06:19 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/08/28 16:15:27 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_num(int n)
{
	int						count;
	unsigned long long int	number;

	count = 0;
	number = n;
	if (n < 0)
	{
		number = -number;
		count += print_char('-');
		if (count == -1)
			return (-1);
	}
	if (number >= 10)
	{
		count += print_num(number / 10);
		if (count == -1)
			return (-1);
		count += print_num(number % 10);
	}
	else
		count += print_char(number + '0');
	return (count);
}
