/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_removal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 21:41:28 by amait-ou          #+#    #+#             */
/*   Updated: 2023/05/29 22:05:27 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	indexer(int i)
{
	if (i < 0)
		return (0);
	return (1);
}

static int	handled_heredoc_delimiter(t_parser *parser, char *token)
{
	if (indexer(parser->i - 1))
	{
		if (!ft_strcmp(parser->tokens[parser->i - 1], "<<"))
		{
			parser->line = string_join(parser->line,
					ft_substr(token, parser->j, ft_strlen(token)));
			return (1);
		}
	}
	return (0);
}

static	void	remove_quotes(t_parser *parser, char *token)
{
	parser->quote = token[parser->j];
	parser->j++;
	while (token[parser->j] != parser->quote && token[parser->j])
	{
		parser->line = string_join(parser->line,
				ft_substr(token, parser->j, 1));
		parser->j++;
	}
}

static void	remove_quote_scanner(t_parser *parser)
{
	char	*token;

	token = parser->tokens[parser->i];
	parser->j = -1;
	while (token[++parser->j])
	{
		if (token[parser->j] == '\"' || token[parser->j] == '\'')
		{
			if (handled_heredoc_delimiter(parser, token))
				break ;
			else
				remove_quotes(parser, token);
		}
		else
			parser->line = string_join(parser->line,
					ft_substr(token, parser->j, 1));
	}
	if (!parser->line)
		parser->line = ft_strdup("");
	free(parser->tokens[parser->i]);
	parser->tokens[parser->i] = parser->line;
}

void	quotes_removal(t_parser *parser)
{
	parser->i = -1;
	while (parser->tokens[++parser->i])
	{
		parser->line = NULL;
		remove_quote_scanner(parser);
	}
}
