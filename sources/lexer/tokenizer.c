/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 11:46:43 by amait-ou          #+#    #+#             */
/*   Updated: 2023/05/12 20:43:15 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

void	quotes(t_lexer *lexer, char *s)
{
	lexer->j = lexer->i++;
	while (s[lexer->i] != lexer->c && s[lexer->i])
		lexer->i++;
	if (s[lexer->i])
	{
		lexer->line = string_join(lexer->line, ft_substr(s, lexer->j,
			lexer->i - lexer->j + 1));
		lexer->line = string_join(lexer->line, ft_strdup("\n"));
	}
}

void	operators(t_lexer *lexer, char *s)
{
	lexer->line = string_join(lexer->line, ft_strdup("\n"));
	lexer->line = string_join(lexer->line, ft_substr(s, lexer->i, 1));
	lexer->line = string_join(lexer->line, ft_strdup("\n"));
}

char 	*scanner(char *s)
{
	t_lexer lexer;

	lexer.i = 0;
	lexer.line = NULL;
	while (s[lexer.i])
	{
		if (s[lexer.i] == '\"' || s[lexer.i] == '\'')
		{
			lexer.c = s[lexer.i];
			quotes(&lexer, s);
		}
		else if (ft_strchr("<>|", s[lexer.i]))
			operators(&lexer, s);
		else if (ft_strchr(" \t\n\v\f\r", s[lexer.i]))
			lexer.line = string_join(lexer.line, ft_strdup("\n"));
		else
			lexer.line = string_join(lexer.line, ft_substr(s, lexer.i, 1));
		lexer.i++;
	}
	return (lexer.line);
}

char **tokenizer(char *s)
{
	char *line;
	char **tokens;

	line = scanner(s);
	tokens = ft_split(line, '\n');
	free(line);
	return (tokens);
}