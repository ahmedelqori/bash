/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-qori <ael-qori@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:13:06 by ael-qori          #+#    #+#             */
/*   Updated: 2024/02/26 10:40:48 by ael-qori         ###   ########.fr       */
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