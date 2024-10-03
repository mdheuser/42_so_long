/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:40:53 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/08/28 16:15:30 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_str(char *s)
{
	int	count;
	int	bytes_written;

	bytes_written = 0;
	count = 0;
	if (!s)
		count = write(1, "(null)", 6);
	else
	{
		while (s[count] != '\0')
		{
			bytes_written = write(1, &s[count], 1);
			if (bytes_written == -1)
				return (-1);
			count++;
		}
		return (count);
	}
	return (count);
}
