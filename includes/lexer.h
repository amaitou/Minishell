/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:50:35 by amait-ou          #+#    #+#             */
/*   Updated: 2023/05/12 20:53:56 by amait-ou         ###   ########.fr       */
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
}	t_lexer;

void	quotes(t_lexer *lexer, char *s);
void	operators(t_lexer *lexer, char *s);
char 	*scanner(char *s);
char	**tokenizer(char *s);
void	tokens_traversal(char **t);

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