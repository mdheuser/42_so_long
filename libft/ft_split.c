/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:03:59 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/05/06 18:56:59 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_initiate_vars(size_t *i, int *j, int *strt_i_word)
{
	*i = 0;
	*j = 0;
	*strt_i_word = -1;
}

static int	count_words(const char *str, int c)
{
	int	i;
	int	counter;
	int	in_word;

	i = 0;
	counter = 0;
	in_word = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c)
		{
			if (in_word == 0)
			{
				counter++;
				in_word = 1;
			}
		}
		else
		{
			in_word = 0;
		}
		i++;
	}
	return (counter);
}

static char	*fill_word(const char *str, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((end - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (start < end)
	{
		word[i] = str[start];
		i++;
		start++;
	}
	word[i] = 0;
	return (word);
}

static void	*cleanup(char **array_of_strs, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(array_of_strs[i]);
		i++;
	}
	free(array_of_strs);
	return (NULL);
}

char	**ft_split(const char *s, char c)
{
	char	**str_array;
	size_t	i;
	int		j;
	int		strt_i_word;

	ft_initiate_vars(&i, &j, &strt_i_word);
	str_array = ft_calloc((count_words(s, c) + 1), sizeof(char *));
	if (!str_array)
		return (NULL);
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && strt_i_word < 0)
			strt_i_word = i;
		else if ((s[i] == c || i == ft_strlen(s)) && strt_i_word >= 0)
		{
			str_array[j] = fill_word(s, strt_i_word, i);
			if (!(str_array[j]))
				return (cleanup(str_array, j));
			strt_i_word = -1;
			j++;
		}
		i++;
	}
	return (str_array);
}
