/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_space_to_pipe.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meedivo <meedivo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 12:55:37 by meedivo           #+#    #+#             */
/*   Updated: 2024/02/27 12:56:31 by meedivo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


int	ft_count_space_pipe(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (i == 0 && s[i] == PIPE && s[i + 1 ]&& s[i + 1] != 32 )
			count++;
		if (i != 0 && s[i] == PIPE && s[i - 1] != 32)
			count++;
		if (i != 0 && s[i] == PIPE && s[i + 1] && s[i + 1] != 32)
			count++;
		i++;
	}
	return (count);
}

char	*ft_add_space_to_pipe(char *s)
{
	int	len;
	int	i;
	int j;
	char *new;

	len = ft_strlen(s) + ft_count_space_pipe(s);
	new = malloc(sizeof(char) * (len + 1));
	if(new == NULL )
		return (NULL);
	i = 0;
	j = 0;
	int tmp = 0;
	while (s[i])
	{
		if (s[i] != PIPE)
		{
			new[j] = s[i];
		}
		else
		{
			tmp = j;
			if (i != 0 && s[i - 1] != 32)
			{
				new[j] = ' ';
				j++;
				new[j] = s[i];
			}
			if (s[i + 1] && s[i + 1] != 32)
			{
				new[j] = s[i];
				j++;
				new[j] = ' ';
			}
			if (tmp == j)
				new[j] = s[i];
		}
		j++;
		i++;
	}
	new[j] = 0;
	return (new);
}