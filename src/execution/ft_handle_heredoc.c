/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meedivo <meedivo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:25:56 by meedivo           #+#    #+#             */
/*   Updated: 2024/03/05 13:49:22 by meedivo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	tree_help_here_doc(t_tree *tree)
{
	t_tree	*root;
	char	*line;

	root = (tree);
	if (!root)
		return;
	if ( root->command[0] == INPUT)
	{
		if (root->left && root->command[0] == INPUT)
		{
			if (ft_strcmp(root->command, HERE_DOC) == 0)
			{
                char *tmp_folder = "./tmp/";
				char *new_str = ft_get_unique_file();
				int new_file = open(ft_strjoin(tmp_folder, new_str), O_CREAT| O_RDWR,0777);
				while ((line = readline("HereDoc $> ")))
				{
					if (ft_strcmp(line, root->left->command) == 0)
						break;
					write(new_file, line, ft_strlen(line));
					write(new_file, "\n", 1);
				}
				close(new_file);
				root->left->command = ft_strjoin(tmp_folder, new_str);
                root->command = ft_strdup("<");
				// unlink(new_str);
			}
		}
	}
	tree_help_here_doc(tree->right);
}

void    ft_handle_heredoc(t_list_pipe **lst)
{
    t_list_pipe *tmp;
    t_tree  *root;
    tmp = (*lst);
    while (tmp)
    {
        root = tmp->root;
        tree_help_here_doc(root);
        tmp = tmp->next;
    }
}