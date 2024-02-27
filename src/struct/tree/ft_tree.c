/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meedivo <meedivo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:12:34 by meedivo           #+#    #+#             */
/*   Updated: 2024/02/27 14:17:07 by meedivo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_tree *ft_new_tree(char *command)
{
    t_tree *root;

    root = malloc(sizeof(t_tree));
    if (root == NULL)
        return (NULL);
    root->command = ft_strdup(command);
    root->left = NULL;
    root->right = NULL;
    return (root);
}

void    ft_tree_insert(t_tree **root, t_tree *new)
{
    if (new == NULL)
        return ;
    if ((*root) == NULL)
        (*root) = new;
	else if (((*root)->command[0] == OUTPUT || (*root)->command[0] == INPUT) && (*root)->left == NULL &&
		(new->command[0] == INPUT || new->command[0] == OUTPUT) 
	)
		return;
	else if (((*root)->command[0] == OUTPUT || (*root)->command[0] == INPUT ) && (*root)->left == NULL )
		(*root)->left = new;
	else if ((*root)->right == NULL)
		(*root)->right = new;
	else	
		ft_tree_insert(&(*root)->right, new);
}