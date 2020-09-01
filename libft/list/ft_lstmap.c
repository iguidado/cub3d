/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 07:48:14 by iguidado          #+#    #+#             */
/*   Updated: 2019/11/25 21:28:12 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static	void	*ft_clear_lst(t_list *l, t_list *last, void (*del)(void *))
{
	t_list *next;

	next = NULL;
	while (l != last)
	{
		next = l->next;
		del(l->content);
		free(l);
		l = NULL;
		l = next;
	}
	del(l->content);
	free(l);
	return (l = NULL);
}

t_list			*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *new;
	t_list *crawl;

	new = NULL;
	crawl = NULL;
	(void)del;
	if (lst)
	{
		if (!(new = (t_list *)malloc(sizeof(t_list))))
			return (NULL);
		new->content = f(lst->content);
		new->next = NULL;
		crawl = new;
		while (lst->next)
		{
			lst = lst->next;
			if (!((crawl->next) = (t_list *)malloc(sizeof(t_list))))
				return (ft_clear_lst(new, crawl, del));
			crawl = crawl->next;
			crawl->content = f(lst->content);
			crawl->next = NULL;
		}
	}
	return (new);
}
