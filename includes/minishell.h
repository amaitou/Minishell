/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 00:07:48 by amait-ou          #+#    #+#             */
/*   Updated: 2023/06/03 12:08:01 by amait-ou         ###   ########.fr       */
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
    int     i;
    int     j;
    char    t_quote;
} t_scanner;

// the token types

typedef enum e_types
{
	__NONE = -1,
	__RED_IN = '<',
	__RED_OUT = '>',
	__RED_APP = '>>',
	__HEREDOC,
	__PIPE = '|'
}	t_types;

// the token state to check the type of quotes

typedef enum e_state
{
    __d_quotes = '\"',
    __s_quotes = '\'',
    __none = -1
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


// doubly linked list functions

t_dlist *create_node(void);
t_dlist *last_node(t_dlist *head);
void    append_node(t_dlist *head, t_dlist *new);
void    traverse_list(t_dlist *head);

// tokenizer functions

int handle_quotes(t_dlist *head, t_scanner *scanner);
int handle_operators(t_dlist *head, t_scanner *scanner);
int command_scanner(t_dlist *head, t_scanner *scanner);
void tokenizer(t_dlist *head, t_scanner *scanner);

#endif