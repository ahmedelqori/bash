/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_syntax_error.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-qori <ael-qori@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:05:10 by ael-qori          #+#    #+#             */
/*   Updated: 2024/02/26 11:33:40 by ael-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_check_after_redirection_input(char *s)
{
	int	i;
	int j;
	int check_space;
	int check_heredoc;
	i = 1;

	check_space = 0;
	check_heredoc = 0;	
	j = 1;
	while (s[j] == ' ')
		j++;
	if (j == (int)ft_strlen(s))
		return (1);
	while (s[i])
	{
		if (s[i] == ' ')
		{
			check_space++;
			i++;
		}
		else if (s[i++] == INPUT && check_space == 0)
			check_heredoc++;
		else if (s[i] == OUTPUT && check_space == 0)
		{
			check_space++;
			i++;
		}
		else if ((s[i] != INPUT &&  ft_is_redirection(s[i])))
			return (1);
		else if  (check_heredoc && s[i] == INPUT )
			return (1);
		else
			break;
	}
	return 0;
}

int ft_check_after_redirection_output(char *s)
{
	int	i;
	int check_space;
	int check_append;
	i = 1;

	check_space = 0;
	check_append = 0;	
	while (s[i])
	{
		if (s[i] == ' ')
		{
			check_space = 1;
			i++;
		}
		if (s[i] == OUTPUT && check_space == 0)
		{
			check_append = 1;
			i++;
		}
		if ((s[i] != OUTPUT &&  ft_is_redirection(s[i])) || (check_append && s[i] == OUTPUT))
			return (1);
	}
	return 0;
}