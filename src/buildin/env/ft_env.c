/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-qori <ael-qori@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 13:10:01 by ael-qori          #+#    #+#             */
/*   Updated: 2024/02/25 13:38:08 by ael-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// ========= CLEAR ENV =========

t_env	*ft_clear_env(t_env **env)
{
	t_env *tmp;

	if (!env)
		return (NULL);
	while (*env)
	{
		free((*env)->key);
		free((*env)->value);
		tmp = (*env);
		(*env) = (*env)->next;
		free(tmp);
	}
	
	return (NULL);
}

// ========= CREATE NEW ENV =========


t_env	*ft_create_env(char **env_arr)
{
	t_env	*env;
	t_env	*node;
	char	*key;
	char	*value;
	int		i;

	i = 0;
	env = NULL;
	if (!env_arr)
		return (NULL);
	while (env_arr[i])
	{
		key = ft_get_key_env(env_arr[i]);
		value = ft_get_value_env(env_arr[i]);	
		node = ft_new_node_env(key, value);
		if (node == NULL)
		{
			free(key);
			free(value);
			return (ft_clear_env(&env));
		}
		ft_addenv_back(&env, node);
		i++;		
	}
	return (env);
}

// ========= PRINT ENV =========


void	ft_print_env(t_env *env)
{
	while (env)
	{
		printf("%s=%s\n",env->key,env->value);
		env = env->next;
	}
}