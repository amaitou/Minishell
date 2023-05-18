/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:50:35 by amait-ou          #+#    #+#             */
/*   Updated: 2023/05/18 20:04:19 by amait-ou         ###   ########.fr       */
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
	char	*line;
	int		error;
	char	quote;
	char	**tokens;
	char	*cmd;
}	t_lexer;

/**
 * @brief Declarations for tokens scanner
 *
 **/

int		quotes(t_lexer *lexer, char *s);
int		operators(t_lexer *lexer, char *s);
int		scanner(char *s, t_lexer *lexer);
char	**tokenizer(t_lexer *lexer);

/**
 * @the traversal that travers over all tokens and prints them
 *
 **/

void	tokens_traversal(char **tokenizer);

void	free_array(char **arr);

#endif
