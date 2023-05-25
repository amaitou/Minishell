/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:27:45 by amait-ou          #+#    #+#             */
/*   Updated: 2023/05/25 17:07:08 by bbouagou         ###   ########.fr       */
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

// struct used by the lexer
typedef struct s_lexer
{
	int		i;
	int		j;
	int		param_exp;
	char	*line;
	int		error;
	char	quote;
	char	**tokens;
	char	*cmd;
}	t_lexer;

// struct used by the prompt string
typedef struct s_prompt
{
	char	*line;
}	t_prompt;

// struct used by the parser

typedef struct s_parser
{
	int		param_exp;
	char	**tokens;
	char	**req;
	char	*p_match;
	char	*matched;
	int		first;
	int		last;
	int		wc_present;
	int		i;
	int		j;
}	t_parser;

typedef enum e_cntrl_op
{
	__RED_IN,
	__RED_OUT,
	__RED_OUT_APP,
	__HEREDOC,
	__PIPE,
	__COMMAND,
	__OR,
	__AND,
	__NONE
}	t_cntrl_op;

typedef struct s_info
{
	char			*full_cmd;
	t_cntrl_op		op;
	struct s_info	*next;
}	t_info;

/**
 * @brief Declarations for tokens scanner
 **/

int		quotes(t_lexer *lexer, char *s);
int		operators(t_lexer *lexer, char *s);
int		scanner(char *s, t_lexer *lexer);
char	**tokenizer(t_lexer *lexer);

/**
 * @brief Declarations for wildcards expander utils funcs
 */

char	*find_format(t_parser *parser, int i);
int		should_expand(char *string);
void	match_found(t_parser *parser);
void	search_for_match(t_parser *parser);
void	wildcards_expander(t_parser *parser);

/**
 * @brief Declarations for variables expander
 */

void	variables_expander(t_parser *parser, t_env *env);

/**
 * @brief Declarations for prompt string (PS)
 **/

char	*prompt_string(t_prompt *prompt);

/**
 * @the traversal that travers over all tokens and prints them
 *
 **/

void	tokens_traversal(char **tokenizer);

/**
 * @bried declaration for environment variables
 **/

t_env	*init_env(t_env	*env, char **envp);
char	*ft_getenv(char *string, t_env *env);

void	free_pointers(t_lexer *lexer, t_prompt *prompt, t_parser *parser);
void	free_array(char **arr);

#endif