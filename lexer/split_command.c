/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 11:46:43 by amait-ou          #+#    #+#             */
/*   Updated: 2023/05/09 19:18:32 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*handle_quotes(char *p, int *q, char c)
{
	*q = 1;
	++p;
	while (*q && *p)
	{
		if (*p == c && *(p + 1) != ' ')
		{
			*q = 0;
			while (*p != ' ' && *p != '\t' && *p)
				++p;
			if (*p)
				*p = 0x3;
		}
		if (*(p + 1) == ' ' && *p == c)
		{
			*q = 0;
			*(p + 1) = 0x3;
		}
		++p;
	}
	return (p);
}

char	*split_command(char *s)
{
	int		q;
	char	*p;
	char	*r;

	q = 0;
	p = ft_strtrim(s, "\t ");
	r = p;
	while (*p)
	{
		if (*p == '"')
			p = handle_quotes(p, &q, '"');
		else if (*p == '\'')
			p = handle_quotes(p, &q, '\'');
		else
		{
			while ((*p != '\t' && *p != ' ') && !q && *p)
				++p;
			if (*p)
				*p = 0x3;
			++p;
		}
	}
	return (r);
}

char	**create_tokens(char *s)
{
	char	*p;
	char	**tokens;

	p = split_command(s);
	tokens = ft_split(p, 0x03);
	return (tokens);
}
