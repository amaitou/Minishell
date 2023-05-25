/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_expander_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 03:28:02 by bbouagou          #+#    #+#             */
/*   Updated: 2023/05/25 16:57:55 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	should_expand(char *string)
{
	int	i;

	i = 0;
	while (string[i] != '$' && string[i])
		i++;
	return (ft_strlen(string) - i);
}

void	match_found(t_parser *parser)
{
	free(parser->tokens[parser->i]);
	parser->tokens[parser->i] = ft_strdup(parser->matched);
	free (parser->matched);
}

static int	search(t_parser *parser, int i, int j)
{
	if (!i && parser->first && !ft_strnstr(parser->p_match + j,
			parser->req[i], ft_strlen(parser->req[i])))
		return (0);
	else if (!parser->req[i + 1] && parser->last
		&& !ft_strlaststr(parser->p_match + j, parser->req[i]))
		return (0);
	else if (!ft_strnstr(parser->p_match + j, parser->req[i],
			ft_strlen(parser->p_match)))
		return (0);
	return (1);
}

void	search_for_match(t_parser *parser)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	if (parser->p_match[0] == '.')
		return ;
	while (parser->req[++i])
	{
		if (!search(parser, i, j))
			break ;
		j = ft_strlen(parser->req[i]);
	}
	if (!parser->req[i])
	{
		parser->matched = string_join(parser->matched, parser->p_match);
		parser->matched = string_join(parser->matched, ft_strdup(" "));
	}
	else
		free (parser->p_match);
}
