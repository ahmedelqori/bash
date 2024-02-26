/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-qori <ael-qori@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:24:47 by ael-qori          #+#    #+#             */
/*   Updated: 2024/02/26 10:09:19 by ael-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_redirection(char c)
{
	if (c == PIPE || c == INPUT || c ==OUTPUT)
		return (1);
	return (0);
}

int	ft_get_index_of_next_quotes(char *s, char c,int i)
{
	i += 1;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

void	ft_replace_pipe_and_redirections(char *s, int start, int end)
{
	while (start < end)
	{
		if ((s[start] == ' ' || ft_is_redirection(s[start])))
			s[start] *= -1;
		start++;
	}
}