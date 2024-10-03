/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:49:48 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/05/02 15:24:03 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(int nbr)
{
	int	n_digits;

	n_digits = 0;
	if (nbr < 0)
		n_digits++;
	while (nbr != 0)
	{
		nbr = nbr / 10;
		n_digits++;
	}
	return (n_digits);
}

static char	*n_to_str(int nbr, int len, int isneg)
{
	char	*str;

	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len > 0)
	{
		len--;
		str[len] = '0' + (nbr % 10);
		nbr = nbr / 10;
	}
	if (isneg == 1)
		str[0] = '-';
	return (str);
}

char	*ft_itoa(int n)
{
	char	*nstr;
	int		nd;
	int		isneg;

	isneg = 0;
	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	nd = count_digits(n);
	if (n < 0)
	{
		isneg = 1;
		n = -n;
	}
	nstr = n_to_str(n, nd, isneg);
	return (nstr);
}
