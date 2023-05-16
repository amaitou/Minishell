/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:50:35 by amait-ou          #+#    #+#             */
/*   Updated: 2023/05/16 17:23:44 by amait-ou         ###   ########.fr       */
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
	char	quote;
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

int		quotes(t_lexer *lexer, char *s);
int		operators(t_lexer *lexer, char *s);
int		scanner(char *s, t_lexer *lexer);
int		tokenizer(t_lexer *lexer);
void	variables_expander(t_lexer *lexer);
void	tokens_traversal(char **tokenizer);
void	free_struct(t_lexer *lexer);
void	wildcards_expander(t_lexer *lexer);
void	free_array(char **arr);
void	free_line(char *s);

#endif
