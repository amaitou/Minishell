/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_removal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 21:41:28 by amait-ou          #+#    #+#             */
/*   Updated: 2023/05/28 18:21:26 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_quotes(t_parser *parser)
{
	char	*token;

	token = parser->tokens[parser->i];
	parser->j = -1;
	while (token[++parser->j])
	{
		if (token[parser->j] == '\"' || token[parser->j] == '\'')
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
		remove_quotes(parser);
	}
}
