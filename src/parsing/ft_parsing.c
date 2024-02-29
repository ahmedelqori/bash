/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meedivo <meedivo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 13:59:23 by ael-qori          #+#    #+#             */
/*   Updated: 2024/02/29 09:01:08 by meedivo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	filter_space_redirections(char *s)
{
	int	i;
	int j;

	i = 0;

	while (s && s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			j = ft_get_index_of_next_quotes(s, s[i], i);
			if (j == -1)
				return (-1);
			ft_replace_pipe_and_redirections(s, i, j);
			i = j;		
		}	
		i++;
	}
	return 0;
}

void	ft_return_real_value(char **arr)
{
	int i;
	int j;

	i = 0;
	while (arr[i])
	{
		j = 0;		
		while (arr[i][j])
		{
			if (arr[i][j] < 0)
				arr[i][j] *= -1;
			j++;
		}
		i++;
	}
}

char	**ft_all_functions(char *s)
{
	char	**arr;
	char	*fix_space_input;
	char	*fix_space_output;
	char	*fix_space_pipe;

	fix_space_input = ft_add_space_to_input(s);
	free(s);
	fix_space_output = ft_add_space_to_output(fix_space_input);
	free(fix_space_input);
	fix_space_pipe = ft_add_space_to_pipe(fix_space_output);		
	free(fix_space_output);
	arr = ft_split(fix_space_pipe, ' ');
	ft_return_real_value(arr);
	free(fix_space_pipe);
	return (arr);
}

char	*ft_get_all_command(char *input)
{
	char	*current;
	char	*tmp;

	while (ft_strtrim(input, " ")[ft_strlen(ft_strtrim(input, " ")) - 1] == '|')
	{
		tmp = readline("> ");
		if (tmp == NULL)
			break;
		current = input;
		input = ft_strjoin(current, tmp);
		free(tmp);
		free(current);	
	}
	return (input);
}

char	**ft_parsing(char *input)
{
	char	*current;
	char	*current1;
	char	*tmp;
	int 	res;

	res = filter_space_redirections(input);
	if (res == -1)
	{
		current = ft_get_all_lines(input);
		filter_space_redirections(current);
		return (ft_all_functions(current));
	}
	tmp = ft_strtrim(input, " ");
	if (tmp[ft_strlen(tmp) - 1] == '|')
	{
		current1 = ft_get_all_command(input);
		filter_space_redirections(current1);
		return (ft_all_functions(current1));	
	}
	current = ft_strdup(input);
	free(input);
	return (ft_all_functions(current));
}
