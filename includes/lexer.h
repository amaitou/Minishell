/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:50:35 by amait-ou          #+#    #+#             */
/*   Updated: 2023/05/13 10:22:31 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "./minishell.h"

typedef struct s_lexer
{
	int		i;
	int		j;
	char	*line;
	char	c;
	char	**tokens;
}	t_lexer;

void	quotes(t_lexer *lexer, char *s);
void	operators(t_lexer *lexer, char *s);
char	*scanner(char *s, t_lexer *lexer);
char	**tokenizer(char *s);
void	tokens_traversal(char **tokenizer);
void	free_tokenizer(char **tokenizer);

typedef enum e_cntrl_op
{
	RED_IN,
	RED_OUT,
	RED_OUT_APP,
	RED_IN_DEL,
	PIPE
}	t_cntrl_op;

typedef struct s_info
{
	char		*full_cmd;
	t_cntrl_op	op;
}	t_info;

#endif
