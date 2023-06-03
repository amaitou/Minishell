/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 00:07:48 by amait-ou          #+#    #+#             */
/*   Updated: 2023/06/03 19:15:45 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../superlib/superlib.h"
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

// struct that goes for the scanner

typedef struct s_scanner
{
    char    *command;
    char    *line;
    char    **tokens;
    int     i;
    int     j;
    char    t_quote;
} t_scanner;

// the token types

typedef enum e_types
{
	__NONE = 0,
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
    __none = 0
} t_state;

// the struct of doubly linked-list in which we'll store our splitted tokens

typedef struct s_dlist
{
    char            *value;
    t_types         type;
    t_state         state;
    struct s_dlist *next;
    struct s_dlist *prev;
} t_dlist;


// prompt functions

void	get_user(t_prompt *prompt);
char	*prompt_string(t_prompt *prompt);

// doubly linked list functions

t_dlist *create_node(void);
t_dlist *last_node(t_dlist *head);
void    append_node(t_dlist *head, t_dlist *new);
void    traverse_list(t_dlist *head);

// scanner functions

void	handle_quotes(t_scanner *scanner);
void	handle_operators(t_scanner *scanner);
void	command_splitter(t_scanner *scanner);
void	__scanner(t_scanner *scanner);
void	scanner_traversal(char **scanner);
void	free_scanner(char **tokens);

// lexer functions
void	__lexer(t_dlist *head, t_scanner *scanner);
void    tokenizer(t_dlist *head, char *token);
t_dlist *node_quotes(char *token, char quote);
t_dlist	*node_redirection(char *token);
t_dlist	*node_pipeline(char *token);
t_dlist *node_word(char *token);

#endif