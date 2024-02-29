/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_child.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meedivo <meedivo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:20:18 by meedivo           #+#    #+#             */
/*   Updated: 2024/02/29 16:47:23 by meedivo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char    *ft_get_right_path(t_env *env ,char *arg)
{
    char    **arr;
    char    *value;
    char    *tmp;
    char    *current;
    int     i;

    i = 0;
    while (env)
    {
        if (ft_strcmp(env->key, "PATH") == 0)
        {
            value = env->value;
            break;
        }
        env = env->next;
    }
    arr = ft_split(value , ':');
    free(value);
    while (arr[i])
    {
        current = ft_strjoin(arr[i], "/");
        tmp = ft_strjoin(current, arg);
        if (access(tmp, F_OK & X_OK ) != -1)
        {
            ft_free_arr(arr);
            return (tmp);
        }
        i++;
        free(tmp);
    }
    ft_free_arr(arr);
    return (NULL);
}

void    ft_handle_child(t_list_pipe *lst, int *files , char **args, int *fd, t_env **env)
{
    char *path;

    path = ft_get_right_path(*env, args[0]);
    if (path == NULL)
    {
        perror("CANT FOUND PATH IN ENV\n");
        exit(1);
    } 
    if (lst->next)
        dup2(fd[1], STDOUT_FILENO);
    if (files[1] != files[3])
        dup2(files[1], STDOUT_FILENO);
    ft_close_all_files(fd,files);
	if (execve(path, args, NULL) < 0)
    {
        perror("ERROR:\t");
        exit(1);
    }
}