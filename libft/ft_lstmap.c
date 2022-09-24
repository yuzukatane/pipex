/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 17:07:25 by kyuzu             #+#    #+#             */
/*   Updated: 2022/05/30 11:15:34 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*top;
	t_list	*newelem;

	if (lst == NULL || f == NULL)
		return (NULL);
	top = NULL;
	while (lst != NULL)
	{
		newelem = ft_lstnew(f(lst->content));
		if (newelem == NULL)
		{
			ft_lstclear(&top, del);
			return (NULL);
		}
		ft_lstadd_back(&top, newelem);
		lst = lst->next;
	}
	return (top);
}
