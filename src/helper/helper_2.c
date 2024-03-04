/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meedivo <meedivo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:13:06 by ael-qori          #+#    #+#             */
/*   Updated: 2024/03/04 19:53:56 by meedivo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_get_unique_file(void)
{
	int		fd;
	char	s[11];
	int		i;

	fd = open("/dev/random",O_RDONLY,0777);
	if (fd == -1)
		return (NULL);
	read(fd, s, 10);
	s[11] = 0;
	char *arr = "0123456789abcdef";
	i = 0;
	int n;
	while (i < 10)
	{
		if (s[i] < 0)
			s[i] *= -1;
		s[i] = s[i] % 16;
		n = s[i];
		s[i] = arr[n];
		i++;
	}
	close(fd);
	return (ft_strdup(s));
}

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
			if (ft_strcmp(root->command, HERE_DOC) == 0)
			{
				char *new_str = ft_get_unique_file();
				int new_file = open(new_str, O_CREAT| O_RDWR,0777);
				while ((line = readline("HereDoc $> ")))
				{
					if (ft_strcmp(line, root->left->command) == 0)
						break;
					write(new_file, line, ft_strlen(line));
					write(new_file, "\n", 1);
				}
				close(new_file);
				*input = open(new_str,O_RDONLY,0777);
				unlink(new_str);
			}
		}
	}
	if (root->command[0] != OUTPUT && root->command[0] != INPUT)
		ft_lstadd_back(list,ft_lstnew(root->command));
	tree_help(tree->right, list,output, input);
}