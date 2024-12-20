/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 09:19:10 by dhuss             #+#    #+#             */
/*   Updated: 2024/10/17 13:00:16 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}
/* int	main(void)
{
	t_list	*head = ft_lstnew("First Element");
	t_list	*two = ft_lstnew("Second Element");
	t_list	*three = ft_lstnew("Third Element");
	t_list	*last;
	ft_lstadd_back(&head, three);
	ft_lstadd_back(&head, two);
	last = ft_lstlast(head);
	printf("%s\n", (char *)last->content);
	return (0);
} */
