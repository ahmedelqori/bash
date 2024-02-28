/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meedivo <meedivo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:13:06 by ael-qori          #+#    #+#             */
/*   Updated: 2024/02/28 15:16:51 by meedivo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_get_all_lines(char *input)
{
	char	*current;
	char	*tmp;

	while (filter_space_redirections(input) == -1)
	{
		tmp = readline("> ");
		if (tmp == NULL)
			break;
		current = ft_strjoin(input, "\n");
		free(input);
		input = ft_strjoin(current, tmp);
		free(tmp);
		free(current);	
	}
	return (input);
}

void	tree_help(t_tree *tree, t_list **list, int *output,int *input )
{
	t_tree	*root;
	char	*current;
	char	*tmp;
	char	*line;
	int fd;

	root = (tree);
	if (!root)
		return;
	if (root->command[0] == OUTPUT || root->command[0] == INPUT)
	{
		if (root->left && root->command[0] == OUTPUT)
		{
			if (ft_strlen(root->command) == 1)
			{
				fd = open(root->left->command,O_CREAT|O_WRONLY|O_TRUNC,0777);
				if (fd != -1)
					*output = fd;
			}
			if (ft_strcmp(root->command, APPEND) == 0)
			{
				fd = open(root->left->command,O_CREAT|O_WRONLY|O_APPEND,0777);
				if (fd != -1)
					*output = fd;	
			}
		}
		if (root->left && root->command[0] == INPUT)
		{
			if (ft_strlen(root->command) == 1)
			{
				fd = open(root->left->command,O_RDONLY,0777);
				if (fd != -1)
					*input = fd;
			}
			if (strcmp(root->command, HERE_DOC) == 0)
			{
				tmp = "";
				while ((line = readline("HereDoc $> ")))
				{
					if (ft_strcmp(line, root->left->command) == 0)
						break;
					current = ft_strjoin(line, "\n");
					line = tmp;
					tmp = ft_strjoin(tmp , current);	
				}
				write(*output, tmp, ft_strlen(tmp));
			}
		}
	}
	if (root->command[0] != OUTPUT && root->command[0] != INPUT)
		ft_lstadd_back(list,ft_lstnew(root->command));
	tree_help(tree->right, list,output, input);
}