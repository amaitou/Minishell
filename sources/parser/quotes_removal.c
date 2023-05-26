/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_removal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 21:41:28 by amait-ou          #+#    #+#             */
/*   Updated: 2023/05/26 23:37:15 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_quotes(t_parser *parser, char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\"' || s[i] == '\'')
		{
			parser->quote = s[i];
			++i;
			while (s[i] != parser->quote && s[i])
			{
				parser->line = string_join(parser->line, ft_substr(s, i, 1));
				++i;
			}
		}
		else
			parser->line = string_join(parser->line, ft_substr(s, i, 1));
		++i;
	}
	parser->line = string_join(parser->line, ft_strdup("\n"));
}

void	quotes_removal(t_parser *parser)
{
	parser->line = NULL;
	parser->i = -1;
	while (parser->tokens[++parser->i])
		remove_quotes(parser, parser->tokens[parser->i]);
	parser->tokens2 = ft_split(parser->line, '\n');
}
