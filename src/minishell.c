/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meedivo <meedivo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 12:45:08 by ael-qori          #+#    #+#             */
/*   Updated: 2024/02/27 14:27:06 by meedivo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	TODO:
		- [x] create env list
		- [o] fix build in export and unset
		- [o] create Prompt
*/

void	print_arr(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		// printf("(%s)\t",arr[i]);
		free(arr[i]);
		i++;
	}
	// printf("\n");
	free(arr);
}

void	minishell(t_env  *env)
{
	char	*input;
	char	**current;

	while  (1)
	{
		ft_signals();
		input = readline(BOLDYELLOW MINISHELL_PROMPT RESET);
		if (input == NULL)
			return ;
		(void)env;
		(void)input;
		add_history(input);
		current = ft_parsing(input);
		print_arr(current);
	}
}

int main(int ac , char **av, char **env_arr)
{
	t_env *env;

	(void)ac;
	(void)av;
	env = ft_create_env(env_arr);
	minishell(env);
	ft_clear_env(&env);
	return 0;
}