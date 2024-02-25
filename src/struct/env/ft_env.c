/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-qori <ael-qori@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 12:56:34 by ael-qori          #+#    #+#             */
/*   Updated: 2024/02/25 13:36:13 by ael-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// ========= CREATE NEW ENV NODE =========

t_env	*ft_new_node_env(char *key, char *value)
{
	t_env *node;

	node = malloc(sizeof(t_env));
	if (node == NULL)
		return (NULL);
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

// ========= ADD NODE BACK TO ENV LIST =========

void	ft_addenv_back(t_env **env, t_env *node)
{
	t_env	*tmp;

	tmp = (*env);
	if (node == NULL)
		return ;
	if ((*env) == NULL)
		(*env) = node;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
}

// ========= GET KEY FROM ENV =========

char	*ft_get_key_env(char *str)
{
	int		i;
	int 	j;
	char	*key;

	i = -1;
	while (str[++i])
		if (str[i] == '=')
			break;
	key = malloc(sizeof(char) * (i + 1));
	if (key == NULL)
		return (NULL);
	j = 0;
	while (j < i)
	{
		key[j] = str[j];
		j++;
	}
	key[j] = '\0';
	return (key);
}

// ========= GET KEY FROM ENV =========

char	*ft_get_value_env(char *str)
{
	int		i;
	char	*value;

	i = -1;
	while (str[++i])
		if (str[i] == '=')
			break;
	value = ft_strdup(str + i + 1);
	return (value);
}

