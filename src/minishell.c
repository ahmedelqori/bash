/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-qori <ael-qori@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 12:45:08 by ael-qori          #+#    #+#             */
/*   Updated: 2024/02/26 10:57:47 by ael-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	TODO:
		- [x] create env list
		- [o] fix build in export and unset
		- [o] create Prompt
*/

void	minishell(t_env  *env)
{
	char	*input;
	char	*current;

	while  (1)
	{
		ft_signals();
		input = readline(BOLDYELLOW MINISHELL_PROMPT RESET);
		if (input == NULL)
			return ;
		(void)env;
		(void)input;
		current = ft_parsing(input);
		add_history(current);
		(void)current;
		free(current);
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