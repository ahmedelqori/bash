/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meedivo <meedivo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:17:24 by meedivo           #+#    #+#             */
/*   Updated: 2024/02/27 14:18:35 by meedivo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_list_pipe	*ft_lstpipe_new(t_tree	*root)
{
	t_list_pipe *lst_pipe;

	lst_pipe = malloc(sizeof(t_list_pipe));
	if (lst_pipe == NULL)
		return (NULL);
	lst_pipe->root = root;
	lst_pipe->next = NULL;
	return (lst_pipe);
}

void	ft_lstpipe_add_back(t_list_pipe **lst, t_list_pipe *new)
{
	t_list_pipe	*head;

	head = *lst;
	if (new == NULL)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		while (head->next)
			head = head->next;
		head->next = new;
	}
}

t_list_pipe	*ft_create_list(char	**arr)
{
	t_list_pipe	*head;
	t_tree		*root;
	int			i;

	i = 0;
	head = NULL;
	while (arr[i])
	{		
		root = NULL;
		while (arr[i] && arr[i][0] != PIPE)
			ft_tree_insert(&root, ft_tree_new(arr[i++]));
		ft_lstpipe_add_back(&head,ft_lstpipe_new(root));
		if (arr[i])
			i++;
	}
	return (head);
}