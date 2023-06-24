/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:56:43 by bbouagou          #+#    #+#             */
/*   Updated: 2023/06/24 00:09:57 by bbouagou         ###   ########.fr       */
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
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <dirent.h>

# define TRUE 1
# define FALSE 0

// error messages

# define PIPE_ERROR "minishell: syntax error near unexpected token `|'"
# define HEREDOC_ERROR "minishell: syntax error near unexpected token `<<'"
# define APPEND_ERROR "minishell: syntax error near unexpected token `>>'"
# define IN_ERROR "minishell: syntax error near unexpected token `<'"
# define OUT_ERROR "minishell: syntax error near unexpected token `>'"
# define QUOTES_ERROR "minishell: unexpected EOF while looking for matching"
# define AMBIGUOUS_ERROR "minishell: ambiguous redirect"
# define SPACE_REDIRECTION_ERROR "minishell: No such file or directory"

// struct for prompt string

typedef struct s_prompt
{
	char	*line;
}	t_prompt;

// enumeration for error handling

typedef enum e_error
{
	no_error,
	error_of_ambiguous,
	error_of_pipeline,
	error_of_redirection_in,
	error_of_redirection_out,
	error_of_redirection_append,
	error_of_redirection_heredoc,
	error_of_single_quotes,
	error_of_double_quotes,
	error_of_space_redirection
}	t_error_types;

typedef struct s_error
{
	t_error_types	error_type;
	int				exit_staus;
}	t_errors;

// struct that goes for the scanner

typedef struct s_scanner
{
	char	*command;
	char	*line;
	char	**tokens;
	int		i;
	int		j;
	char	t_quote;
	int		error;
}	t_scanner;

// the token types

typedef enum e_types
{
	__WORD = 0,
	__RED_IN = '<',
	__RED_OUT = '>',
	__RED_APP,
	__HEREDOC,
	__PIPE = '|'
}	t_types;

// the token state to check the type of quotes

typedef enum e_state
{
	__d_quotes = '\"',
	__s_quotes = '\'',
	__without_quotes = 0
}	t_state;

// struct of the parser

typedef struct s_parser
{
	char			**args;
	t_list			*file;
	t_list			*heredoc;
	t_types			type;
	struct s_parser	*next;
	struct s_parser	*prev;
}	t_parser;

// the struct of doubly linked-list in which we'll store our splitted tokens

typedef struct s_dlist
{
	int				param_exp;
	int				i;
	int				first;
	int				last;
	int				wc_present;
	char			**req;
	char			*matched;
	char			*p_match;
	char			*value;
	t_types			type;
	t_state			state;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}	t_dlist;

typedef struct s_minishell
{
	t_prompt	*prompt;
	t_errors	*error;
	t_scanner	*scanner;
	t_dlist		*lexer;
	t_parser	*parser;
}	t_minishell;

// execution unit struct

typedef struct s_exec
{
	t_parser	*lst;
	pid_t		pid;
	int			pipefd[2];
	int			heredoc[2];
	int			old_fd;
	int			saved_stdout;
	int			saved_stdin;
	int			nb_commands;
}	t_exec;

// global variable to hold the exit status of the last command

typedef struct s_vars
{
	int		exit_status;
	char	**env;
}	t_vars;

// global variable to store exit_status and env

t_vars				*g_vars;

// prompt functions

void		get_user(t_prompt *prompt);
char		*prompt_string(t_prompt *prompt);

// __scanner__ functions

void		__scanner__(t_minishell *minishell);
void		handle_quotes(t_minishell *minishell);
void		handle_operators(t_minishell *minishell);
void		command_splitter(t_minishell *minishell);
void		display_scanner(char **scanner);

// doubly linked list functions for lexer

t_dlist		*create_node(void);
t_dlist		*last_node(t_dlist *head);
void		append_node(t_dlist **head, t_dlist *new);
void		free_nodes(t_dlist *head, int boolean);

// __lexer__ functions

void		__lexer__(t_minishell *minishell);
void		tokenizer(t_dlist **lexer, char *token);
t_dlist		*node_quotes(char *token, char quote);
t_dlist		*node_redirection(char *token);
t_dlist		*node_pipeline(char *token);
t_dlist		*node_word(char *token);
void		display_lexer_helper(t_dlist *temp);
void		display_lexer(t_dlist *head);
void		quotes_removal(t_dlist *lexer);
void		display_lexer_helper(t_dlist *head);

// __error__ functions

void		__error__(t_minishell *minishell);
void		error_types(t_dlist *node, t_errors *error);
int			error_for_quotes(t_dlist *node);
int			check_errors(t_dlist *temp, t_errors *error);
void		display_error(t_errors *error);

// __parser__functions

void		__parser__(t_parser **parser, t_dlist *lexer);
t_parser	*__create_node(void);
t_parser	*__last_node(t_parser *head);
void		__append_node(t_parser **head, t_parser *new);
int			check_redirection(t_dlist *lexer);
int			check_args(t_dlist *lexer);
void		assign_file(t_dlist *lexer, t_list *file, t_list **node);
void		assign_args(t_dlist *lexer, char **args);
void		display_parser(t_parser *parser);
void		display_for_args(char **args);

// leaks functions

void		free_tokens(char **tokens);
void		del(void	*string);
void		clear_lexer(t_dlist **lst, void (*del)(void *));
void		clear_parser(t_parser **lst, void (*del)(void *));
void		clear_file(t_list **lst, void (*del)(void *));
void		leaks_one(t_minishell *minishell);
void		leaks_two(t_minishell *minishell);

// minishell
void		__parse_and_execute__(t_minishell *minishell);
int			count_number_of_names(char **names, t_errors *error);
void		check_ambiguous(t_dlist *lexer, t_errors *error);
int			error_ambiguous(t_minishell *minishell);
int			initialize_minishell(t_minishell *minishell);
int			check_spaces(char *s);
char		**set_env(char **envp);
void		signal_handler(int signal, siginfo_t *siginfo, void *context);

// env fetching
char		*ft_getenv(char *name, char *env[]);
void		ft_setenv(char *name, char *newval, char *env[]);

// parameters expansion
void		params_expander(t_dlist *list, char *env[]);
int			is_valid(char c);
int			skip_quotes(char *string, int i);
char		quote_type(char quote);

// wildcards expansion
void		wildcards_expander(t_dlist *list);
void		search_for_match(t_dlist *list);
void		match_found(t_dlist *list);
int			should_expand(char *string);

// execution unit functions declarations
void		executor(t_parser *list);
void		pipes_handle(t_parser *list, int old_fd, int *pipefd, int *heredoc);
void		get_exit_status(pid_t pid, t_exec *lst);
void		clean(char **var);
void		close_fds(t_exec *es, t_parser *list);
void		multi_purpose_func(t_exec *es, char *string, int flag);
int			is_dir(char *filename);
t_list		*mount_heredoc(t_list *files);
t_exec		*init_struct(t_parser *list);

// builtins
int			ft_cd(char **args, char *env[], t_parser *list);
int			ft_echo(char **args, t_parser *list);
int			ft_env(char **env, t_parser *list);
int			ft_exit(char **args, t_parser *list);
int			ft_export(char **args, t_parser *list);
int			ft_pwd(char **args, t_parser *list);
int			ft_unset(char **args, t_parser *list);
int			get_env_nb(char **env);
char		*setup_variable(char **args, int i, int flag);
void		ft_free_pointers(char *ptr1, char *ptr2, char *ptr3);
void		print_variable(char *value);

// redirections
int			redirect_output(t_list *list);
int			redirect_input(t_list *list);
int			redirections_handle(t_list *files);
int			append_output(t_list *list);
void		heredoc_handle(t_list *list, int *heredoc);

#endif
