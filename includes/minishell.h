/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 00:07:48 by amait-ou          #+#    #+#             */
/*   Updated: 2023/06/14 13:19:06 by bbouagou         ###   ########.fr       */
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

// struct for prompt string

typedef struct s_prompt
{
	char	*line;
}	t_prompt;

typedef enum e_error
{
	no_error,
	error_of_single_quotes,
	error_of_double_quotes,
	error_of_pipeline,
	error_of_redirection_in,
	error_of_redirection_out,
	error_of_redirection_append,
	error_of_redirection_heredoc
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
	t_types			type;
	struct s_parser	*next;
	struct s_parser	*prev;
}	t_parser;

// the struct of doubly linked-list in which we'll store our splitted tokens

typedef struct s_dlist
{
	// variables needed in expansion;
	int				param_exp;
	int				i;
	// endl
	char			*value;
	t_types			type;
	t_state			state;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}	t_dlist;

// prompt functions

void	get_user(t_prompt *prompt);
char	*prompt_string(t_prompt *prompt);

// doubly linked list functions for lexer

t_dlist	*create_node(void);
t_dlist	*last_node(t_dlist *head);
void	append_node(t_dlist **head, t_dlist *new);
void	traverse_list(t_dlist *head);
void	free_nodes(t_dlist *head, int boolean);

// scanner functions

void	__scanner__(t_scanner *scanner);
void	handle_quotes(t_scanner *scanner);
void	handle_operators(t_scanner *scanner);
void	command_splitter(t_scanner *scanner);
void	free_scanner(char **tokens);

// lexer functions
void	__lexer__(t_dlist **head, t_scanner *scanner);
void	tokenizer(t_dlist **head, char *token);
t_dlist	*node_quotes(char *token, char quote);
t_dlist	*node_redirection(char *token);
t_dlist	*node_pipeline(char *token);
t_dlist	*node_word(char *token);
void	remove_quotes(t_dlist *head, char quote);
void	quotes_removal(t_dlist *head);

// error fucntions

void	__error__(t_dlist *head, t_errors *error);
void	display_error(t_errors *error);

// minishell functions

int		check_spaces(char *s);
void	free_pointers(t_prompt *prompt, t_scanner *scanner, t_errors *error);
int		__check__(t_scanner *scanner, t_prompt *prompt, t_errors *error);
void	__parse__(t_scanner *scanner, t_dlist *head, t_errors *error,
			t_prompt *prompt, char *env[]);

// doubly linked list functions for parser

t_parser	*__create_node(void);
t_parser	*__last_node(t_parser *head);
void	__append_node(t_parser **head, t_parser *new);

// parser function

void	__parser__(t_parser **parser, t_dlist *head);
// int		count_files(t_dlist	*head);
int		count_arguments(t_dlist *head);
// void	assign_file(t_dlist *head, t_parser *node, int i);
void	assign_args(t_dlist *head, t_parser *node, char *args);

// traversing

void	lexer_traverse(t_dlist *head);
void	scanner_traversal(char **scanner);
void	parser_traversal(t_parser *head);

// env fetching
char 	*ft_getenv(char *nam, char *env[]);

// parameters expansion
void	params_expander(t_dlist *list, char *env[]);
int		get_index(char *token);
int		is_valid(char c);
int		skip_quotes(char *string);

#endif
