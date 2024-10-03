/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 19:47:10 by mdahlstr          #+#    #+#             */
/*   Updated: 2024/05/08 13:37:52 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (new == NULL)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	if (!last)
		*lst = new;
	last->next = new;
}
/* Adds the node ’new’ at the end of the list.
 *
 * lst:  The address of a pointer to the first link of
 * a list.
 * new:  The address of a pointer to the node to be
 * added to the list. */
