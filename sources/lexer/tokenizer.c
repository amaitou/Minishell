/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 11:46:43 by amait-ou          #+#    #+#             */
/*   Updated: 2023/05/26 21:10:23 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	quotes(t_lexer *lexer, char *s)
{
	lexer->j = lexer->i++;
	while (s[lexer->i] != lexer->quote && s[lexer->i])
		lexer->i++;
	if (s[lexer->i])
		lexer->line = string_join(lexer->line, ft_substr(s, lexer->j,
					lexer->i - lexer->j + 1));
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

char	**tokenizer(t_lexer *lexer)
{
	lexer->i = 0;
	lexer->line = NULL;
	lexer->error = scanner(lexer->cmd, lexer);
	if (lexer->error)
		return (free(lexer->line), (void *)0);
	else
	{
		lexer->tokens = ft_split(lexer->line, '\n');
		free(lexer->line);
	}
	return (lexer->tokens);
}
