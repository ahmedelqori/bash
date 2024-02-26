/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-qori <ael-qori@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 13:59:23 by ael-qori          #+#    #+#             */
/*   Updated: 2024/02/26 10:35:34 by ael-qori         ###   ########.fr       */
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

char	*ft_parsing(char *input)
{
	char	*current;
	int 	res;

	res = filter_space_redirections(input);
	if (res == -1)
	{
		current = ft_get_all_lines(input);
		filter_space_redirections(current);
		return (current);
	}
	current = ft_strdup(input);
	free(input);
	return (current);
}
