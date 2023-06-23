/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 10:37:57 by amait-ou          #+#    #+#             */
/*   Updated: 2023/06/23 12:11:08 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	tokenizer(t_dlist **lexer, char *token)
{
	if (token[0] == '\'' || token[0] == '\"')
	{
		if (token[0] == '\'')
			append_node(lexer, node_quotes(token, '\''));
		else if (token[0] == '\"')
			append_node(lexer, node_quotes(token, '\"'));
	}
	else if (!ft_strcmp(token, ">") || !ft_strcmp(token, "<")
		|| !ft_strcmp(token, ">>") || !ft_strcmp(token, "<<"))
		append_node(lexer, node_redirection(token));
	else if (!ft_strcmp(token, "|"))
		append_node(lexer, node_pipeline(token));
	else
		append_node(lexer, node_word(token));
}

void	assign_token(t_dlist **lexer, char *token)
{
	free((*lexer)->value);
	if (token)
		(*lexer)->value = ft_strdup(token);
	else
		(*lexer)->value = NULL;
	(*lexer) = (*lexer)->next;
	free(token);
}

void	join_chars(t_dlist *lexer, int *i, char **token)
{
	char	quote;

	if (lexer->value[*i] == '\'' || lexer->value[*i] == '\"')
	{
		quote = lexer->value[(*i)++];
		if (lexer->value[*i] == quote)
			*token = string_join(*token, ft_strdup("\0"));
		else
		{
			while (lexer->value[*i] != quote && lexer->value[*i])
				*token = string_join(*token,
						ft_substr(lexer->value, (*i)++, 1));
		}
	}
	else
		*token = string_join(*token, ft_substr(lexer->value, *i, 1));
}

void	quotes_removal(t_dlist *lexer)
{
	int		i;
	char	*token;

	while (lexer)
	{
		i = 0;
		token = NULL;
		while (lexer->value[i])
		{
			join_chars(lexer, &i, &token);
			++i;
		}
		assign_token(&lexer, token);
	}
}

void	__lexer__(t_minishell *minishell)
{
	t_scanner	*scanner;
	t_dlist		**lexer;

	scanner = minishell->scanner;
	lexer = &minishell->lexer;
	scanner->i = 0;
	while (scanner->tokens[scanner->i])
	{
		tokenizer(lexer, scanner->tokens[scanner->i]);
		scanner->i++;
	}
	free(minishell->scanner->tokens);
}
