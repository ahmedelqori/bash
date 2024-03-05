/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_child.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meedivo <meedivo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:20:18 by meedivo           #+#    #+#             */
/*   Updated: 2024/03/05 11:30:43 by meedivo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char    *ft_get_right_path(t_env *env ,char *arg)
{
    char    **arr;
    char    *value;
    char    *tmp;
    char    *current;
    char    *pwd;
    int     i;

    i = 0;
    while (env)
    {
        if (ft_strcmp(env->key, "PATH") == 0)
            value = env->value;
        if (ft_strcmp(env->key, "PWD") == 0)
            pwd = env->value ;
        env = env->next;
    }
    arr = ft_split(value , ':');
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
    current = ft_strjoin(pwd, "/");
    tmp = ft_strjoin(current, arg + 2);
    free(current);
    ft_free_arr(arr);
    return (tmp);
}

void    ft_handle_child(t_list_pipe *lst, int *files , char **args, int *fd, t_env **env,char **env_arr)
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
	if (execve(path, args, env_arr) < 0)
    {
        perror("Execve\t");
        exit(1);
    }
}