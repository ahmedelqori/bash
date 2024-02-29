/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meedivo <meedivo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 12:41:55 by ael-qori          #+#    #+#             */
/*   Updated: 2024/02/29 16:36:55 by meedivo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL
#define MINISHELL


/*========================= LIBRARY =========================*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "../libft/libft.h"

/*========================= COLORS =========================*/


#define RESET "\033[0m"
#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define BOLDBLACK "\033[1m\033[30m"
#define BOLDRED "\033[1m\033[31m"
#define BOLDGREEN "\033[1m\033[32m"
#define BOLDYELLOW "\033[1m\033[33m"
#define BOLDBLUE "\033[1m\033[34m"
#define BOLDMAGENTA "\033[1m\033[35m"
#define BOLDCYAN "\033[1m\033[36m"
#define BOLDWHITE "\033[1m\033[37m"

/*========================= MACROS =========================*/

#define MINISHELL_PROMPT "MiniShell $> "
#define HOME "HOME"
#define PWD "PWD"
#define OLDPWD "OLDPWD"

#define PIPE '|'
#define INPUT '<'
#define OUTPUT '>'
#define APPEND ">>"
#define HERE_DOC "<<"

/*========================= STRUCT =========================*/

typedef struct s_env
{
	char		 *key;
	char		 *value;
	struct s_env *next;
} t_env;

typedef struct s_tree
{
    char			*command;
    struct s_tree	*left;
    struct s_tree	*right;
} t_tree;

typedef struct s_list_pipe
{
    t_tree  			*root;
    struct s_list_pipe	*next;
}	t_list_pipe;


// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

/*========================= ENV =========================*/

t_env	*ft_new_node_env(char *key, char *value);
t_env	*ft_create_env(char **env_arr);
t_env	*ft_clear_env(t_env **env);
void	ft_addenv_back(t_env **env, t_env *node);
void	ft_print_env(t_env *env);
char	*ft_get_key_env(char *str);
char	*ft_get_value_env(char *str);

/*========================= SIGNALS =========================*/

void    ft_handle_sigint(int sig);
void    ft_signals(void);
/*========================= FREE =========================*/

void    ft_free_arr(char **arr);
/*========================= PARSING =========================*/
int	filter_space_redirections(char *s);

char	**ft_parsing(char *input);
/*========================= HELPER =========================*/
int	ft_is_redirection(char c);
int	ft_get_index_of_next_quotes(char *s, char c,int i);
void	ft_replace_pipe_and_redirections(char *s, int start, int end);
char	*ft_get_all_lines(char *input);
int ft_check_after_redirection_input(char *s);
void	tree_help(t_tree *tree, t_list **list, int *output,int *input );
char	*ft_add_space_to_pipe(char *s);
char	*ft_add_space_to_output(char *s);
char	*ft_add_space_to_input(char *s);

/*========================= TREE =========================*/
t_tree *ft_new_tree(char *command);
void    ft_tree_insert(t_tree **root, t_tree *new);

/*========================= pipe =========================*/

t_list_pipe	*ft_create_list(char	**arr);

void    ft_execution(char **arr ,t_env **env);
void    ft_handle_child(t_list_pipe *lst, int *files , char **args, int *fd, t_env **env);
void    ft_close_all_files(int *fd, int *files);
#endif