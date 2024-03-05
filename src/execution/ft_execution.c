/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meedivo <meedivo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:00:27 by meedivo           #+#    #+#             */
/*   Updated: 2024/03/05 13:47:07 by meedivo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char    **ft_get_all_arguments(t_list *list)
{
    char    **arr;
    int     size;
    int     i;

    size = ft_lstsize(list);
    arr = malloc((size + 1) * sizeof(char *));
    if (arr == NULL)
        return (NULL);
    i = 0;
    while (i < size)
    {
        arr[i] = list->content;
        list = list->next;
        i++;
    }
    arr[size] = NULL;
    return (arr);
}

void    ft_initialize_files(int *arr)
{
    arr[0] = dup(STDIN_FILENO);
    arr[1] = dup(STDOUT_FILENO);
    arr[2] = arr[0];
    arr[3] = arr[1];
}

void    ft_close_all_files(int *fd, int *files)
{
    close(fd[0]);
    close(fd[1]);
    close(files[0]);
    close(files[1]);
    close(files[2]);
    close(files[3]);
}

void    ft_start_execution(t_list_pipe *list, int *fd, t_env **env,char **env_arr )
{
    t_list  *lst;
    char    **args;
    int     files[4];
    int     pid;

    lst = NULL;
    ft_initialize_files(files);
    tree_help(list->root, &lst, &files[1],&files[0]);
    args = ft_get_all_arguments(lst);
    pid = fork();
	if (files[0] != files[2])
		dup2(files[0] , STDIN_FILENO);
    if (pid == 0)
        ft_handle_child(list, files, args ,fd ,env, env_arr);
    else
    {
        if (list->next)
            dup2(fd[0], STDIN_FILENO);
        ft_close_all_files(fd, files);
    }   
}

void    ft_execution(char **arr ,t_env **env, char **env_arr)
{
    int         fd[2];
    t_list_pipe *list;
     t_list_pipe *tmp;
   
    int i  = 0;
    int         org_stdin;
    int         org_stdout;


    org_stdin = dup(STDIN_FILENO);
    org_stdout = dup(STDOUT_FILENO);
    list = ft_create_list(arr);
    ft_handle_heredoc(&list);
    tmp = list;
    while (tmp)
    {
        tmp = tmp->next;
        i++;
    }
    while (list)
    {
        pipe(fd);
        ft_start_execution(list, fd ,env, env_arr) ;
        list = list->next;
    }
    dup2(org_stdin, STDIN_FILENO);
    dup2(org_stdout, STDOUT_FILENO);
    close(org_stdin);
    close(org_stdout);
    int j = 0;
    j = 0;
    while (j < i)
    {
        wait(NULL);
        j++;
    }
}
