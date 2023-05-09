/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 11:37:36 by amait-ou          #+#    #+#             */
/*   Updated: 2023/05/09 16:46:12 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../minishell.h"

char	*handle_quotes(char *p, int *q, char c);
char	*split_command(char *s);
char	**create_tokens(char *s);
void	tokens_traversal(char **t);

#endif