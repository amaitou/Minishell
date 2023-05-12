/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 11:37:36 by amait-ou          #+#    #+#             */
/*   Updated: 2023/05/12 17:28:16 by amait-ou         ###   ########.fr       */
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

#endif