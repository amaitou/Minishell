/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:27:45 by amait-ou          #+#    #+#             */
/*   Updated: 2023/06/14 10:23:01 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../superlib/superlib.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <dirent.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <dirent.h>
# include <errno.h>
# include <stddef.h>

char	**g_env;

// struct used by the prompt string
typedef struct s_prompt
{
	char	*line;
}	t_prompt;

// struct used by the parser

typedef struct s_parser
{
	char	**tokens;
	char	**req;
	char	*line;
	char	*p_match;
	char	*matched;
	char	*cmd;
	int		first;
	int		error;
	int		param_exp;
	int		last;
	int		wc_present;
	int		i;
	int		j;
	char	quote;
}	t_parser;

typedef enum e_types
{
	__NONE = 0,
	__RED_IN = '<',
	__RED_OUT = '>',
	__RED_APP,
	__HEREDOC,
	__PIPE = '|'
}	t_types;

typedef struct s_info
{
	char			*full_cmd;
	t_types			op;
	struct s_info	*next;
}	t_info;

typedef struct s_dlist
{
	char			*cmd;
	char			**args;
	t_types			type;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}	t_dlist;

// EXECUTION FUNCTIONS

t_dlist	*create_node(void);
t_dlist	*last_node(t_dlist *head);
void	append_node(t_dlist **head, t_dlist *new);
void	traverse_list(t_dlist *head);
void	free_nodes(t_dlist *head, int boolean);

void	executor(t_dlist *list, int *status, char *env[]);

int		ft_cd(char **args, char *const env[]);
int		ft_echo(char **args);
int		ft_env(char *const env[]);
int		ft_exit(char **args);
int		ft_export(char **args, char *const env[]);
int		ft_pwd(void);
int		ft_unset(char **args, char **env[]);

#endif