/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 11:46:43 by amait-ou          #+#    #+#             */
/*   Updated: 2023/05/28 18:16:40 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	quotes(t_parser *parser, char *s)
{
	parser->j = parser->i++;
	while (s[parser->i] != parser->quote && s[parser->i])
		parser->i++;
	if (s[parser->i])
		parser->line = string_join(parser->line, ft_substr(s, parser->j,
					parser->i - parser->j + 1));
	else
		return (1);
	return (0);
}

int	operators(t_parser *parser, char *s)
{
	if (!ft_memcmp(s + parser->i, ">>>", 3)
		|| !ft_memcmp(s + parser->i, "<<<", 3)
		|| !ft_memcmp(s + parser->i, "&&&", 3)
		|| !ft_memcmp(s + parser->i, "|||", 3))
		return (2);
	else if (!ft_memcmp(s + parser->i, ">>", 2)
		|| !ft_memcmp(s + parser->i, "<<", 2)
		|| !ft_memcmp(s + parser->i, "||", 2)
		|| !ft_memcmp(s + parser->i, "&&", 2))
	{
		parser->line = string_join(parser->line, ft_strdup("\n"));
		parser->line = string_join(parser->line, ft_substr(s, parser->i, 2));
		parser->line = string_join(parser->line, ft_strdup("\n"));
		parser->i++;
	}
	else
	{
		parser->line = string_join(parser->line, ft_strdup("\n"));
		parser->line = string_join(parser->line, ft_substr(s, parser->i, 1));
		parser->line = string_join(parser->line, ft_strdup("\n"));
	}
	return (0);
}

int	scanner(char *s, t_parser *parser)
{
	while (s[parser->i])
	{
		if (s[parser->i] == '\"' || s[parser->i] == '\'')
		{
			parser->quote = s[parser->i];
			if (quotes(parser, s))
				return (1);
		}
		else if (ft_strchr("<>|&", s[parser->i]))
		{
			if (operators(parser, s))
				return (2);
		}
		else if (ft_strchr(" \t\n\v\f\r", s[parser->i]))
			parser->line = string_join(parser->line, ft_strdup("\n"));
		else
			parser->line = string_join(parser->line,
					ft_substr(s, parser->i, 1));
		parser->i++;
	}
	return (0);
}

void	tokenizer(t_parser *parser)
{
	parser->i = 0;
	parser->line = NULL;
	parser->error = scanner(parser->cmd, parser);
	if (parser->error)
		return (free(parser->line));
	else
	{
		parser->tokens = ft_split(parser->line, '\n');
		free(parser->line);
	}
}
