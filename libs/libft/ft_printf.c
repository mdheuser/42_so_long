/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:31:01 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/08/28 16:16:09 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	print_format(char specifier, va_list args)
{
	int	count;

	count = 0;
	if (specifier == 'c')
		count += print_char(va_arg(args, int));
	else if (specifier == 's')
		count += print_str(va_arg(args, char *));
	else if (specifier == 'p')
		count += print_address(va_arg(args, unsigned long int));
	else if (specifier == 'd' || specifier == 'i')
		count += print_num(va_arg(args, int));
	else if (specifier == 'u')
		count += print_unsigned(va_arg(args, unsigned int));
	else if (specifier == 'x' || specifier == 'X')
		count += print_hex(va_arg(args, unsigned int), specifier);
	else if (specifier == '%')
		count += print_char('%');
	else
		return (-1);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	va_start(args, format);
	if (!format)
		return (-1);
	count = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			count += print_format(*format, args);
		}
		else
			count += write(1, format, 1);
		if (count == -1)
			break ;
		format++;
	}
	va_end(args);
	return (count);
}
