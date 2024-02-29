/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_child.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meedivo <meedivo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:20:18 by meedivo           #+#    #+#             */
/*   Updated: 2024/02/29 11:52:18 by meedivo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    ft_handle_child(t_list_pipe *lst, int *files , char **args, int *fd)
{
    if (lst->next)
        dup2(fd[1], STDOUT_FILENO);
    if (files[1] != files[3])
        dup2(files[1], STDOUT_FILENO);
    ft_close_all_files(fd,files);
	if (execve(ft_strjoin("/usr/bin/", args[0]), args, NULL) < 0)
    {
        perror("ERROR:\t");
        exit(1);
    }
}