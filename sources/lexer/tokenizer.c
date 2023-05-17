/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 11:46:43 by amait-ou          #+#    #+#             */
/*   Updated: 2023/05/17 02:38:43 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

int	quotes(t_lexer *lexer, char *s)
{
	lexer->j = lexer->i++;
	while (s[lexer->i] != lexer->quote && s[lexer->i])
		lexer->i++;
	if (s[lexer->i])
	{
		lexer->line = string_join(lexer->line, ft_substr(s, lexer->j,
					lexer->i - lexer->j + 1));
		lexer->line = string_join(lexer->line, ft_strdup("\n"));
	}
	else
		return (1);
	return (0);
}

int	operators(t_lexer *lexer, char *s)
{
	if (!ft_memcmp(s + lexer->i, ">>>", 3)
		|| !ft_memcmp(s + lexer->i, "<<<", 3)
		|| !ft_memcmp(s + lexer->i, "&&&", 3)
		|| !ft_memcmp(s + lexer->i, "|||", 3))
		return (2);
	else if (!ft_memcmp(s + lexer->i, ">>", 2)
		|| !ft_memcmp(s + lexer->i, "<<", 2)
		|| !ft_memcmp(s + lexer->i, "||", 2)
		|| !ft_memcmp(s + lexer->i, "&&", 2))
	{
		lexer->line = string_join(lexer->line, ft_strdup("\n"));
		lexer->line = string_join(lexer->line, ft_substr(s, lexer->i, 2));
		lexer->line = string_join(lexer->line, ft_strdup("\n"));
		lexer->i++;
	}
	else
	{
		lexer->line = string_join(lexer->line, ft_strdup("\n"));
		lexer->line = string_join(lexer->line, ft_substr(s, lexer->i, 1));
		lexer->line = string_join(lexer->line, ft_strdup("\n"));
	}
	return (0);
}

int	scanner(char *s, t_lexer *lexer)
{
	while (s[lexer->i])
	{
		if (s[lexer->i] == '\"' || s[lexer->i] == '\'')
		{
			lexer->quote = s[lexer->i];
			if (quotes(lexer, s))
				return (1);
		}
		else if (ft_strchr("<>|&", s[lexer->i]))
		{
			if (operators(lexer, s))
				return (2);
		}
		else if (ft_strchr(" \t\n\v\f\r", s[lexer->i]))
			lexer->line = string_join(lexer->line, ft_strdup("\n"));
		else
			lexer->line = string_join(lexer->line, ft_substr(s, lexer->i, 1));
		lexer->i++;
	}
	return (0);
}

int	tokenizer(t_lexer *lexer)
{
	int	scanner_value;

	lexer->i = 0;
	lexer->line = NULL;
	scanner_value = scanner(lexer->cmd, lexer);
	if (scanner_value)
		return (free(lexer->line), scanner_value);
	else
	{
		lexer->tokens = ft_split(lexer->line, '\n');
		free(lexer->line);
		variables_expander(lexer);
	}
	return (0);
}
