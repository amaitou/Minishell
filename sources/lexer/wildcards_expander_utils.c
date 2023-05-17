/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_expander_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 03:28:02 by bbouagou          #+#    #+#             */
/*   Updated: 2023/05/17 03:47:57 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

int	find_len(t_lexer *lexer, int i)
{
	if (lexer->wc_is_last && lexer->req[0])
		return (ft_strlen(lexer->req[i]));
	else
		return (ft_strlen(lexer->p_match));
}

char	*find_format(t_lexer *lexer, int i)
{
	if (!lexer->req[0])
		return (lexer->p_match);
	else
		return (lexer->req[i]);
}

int	should_expand(char *string)
{
	int	i;

	i = 0;
	while (string[i] != '$' && string[i])
		i++;
	return (ft_strlen(string) - i);
}

void	match_found(t_lexer *lexer)
{
	free(lexer->tokens[lexer->i]);
	lexer->tokens[lexer->i] = ft_strdup(lexer->matched);
	free (lexer->matched);
}

void	match_not_found(t_lexer *lexer)
{
	printf("no matches found: %s\n", lexer->tokens[lexer->i]);
	free(lexer->tokens[lexer->i]);
	lexer->tokens[lexer->i] = ft_strdup("");
}
