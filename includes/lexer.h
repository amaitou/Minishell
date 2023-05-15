/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:50:35 by amait-ou          #+#    #+#             */
/*   Updated: 2023/05/16 00:55:27 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "./minishell.h"

typedef struct s_lexer
{
	int		i;
	int		j;
	int		param_exp;
	int		wc_is_last;
	char	*line;
	char	c;
	char	**tokens;
	char	**req;
	char	*p_match;
	char	*matched;
	char	*cmd;
}	t_lexer;

typedef enum e_cntrl_op
{
	RED_IN,
	RED_OUT,
	RED_OUT_APP,
	RED_IN_DEL,
	PIPE,
	COMMAND
}	t_cntrl_op;

typedef struct s_info
{
	char			*full_cmd;
	t_cntrl_op		op;
	struct s_info	*next;
}	t_info;

void	quotes(t_lexer *lexer, char *s);
void	operators(t_lexer *lexer, char *s);
char	*scanner(char *s, t_lexer *lexer);
void	tokenizer(t_lexer *lexer);
void	expand_variables(t_lexer *lexer);
void	tokens_traversal(char **tokenizer);
void	free_struct(t_lexer *lexer);
void	expand_wildcards(t_lexer *lexer);

#endif
