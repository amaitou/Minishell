/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 14:56:20 by bbouagou          #+#    #+#             */
/*   Updated: 2023/05/18 21:40:09 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_index(char *token)
{
	int	i;

	i = 0;
	while (token[i] && !ft_strchr("$\'", token[i]))
		i++;
	return (--i);
}

static int	is_valid(char c)
{
	if (ft_isalpha(c) || ft_isdigit(c) || c == '_')
		return (1);
	else
		return (0);
}

static void	truncate_digit(t_parser *parser)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	tmp = (void *)0;
	while (parser->tokens[parser->i][i] != '$')
		i++;
	if (i)
		tmp = ft_substr(parser->tokens[parser->i], 0, i);
	tmp2 = parser->tokens[parser->i];
	parser->tokens[parser->i] = ft_substr(parser->tokens[parser->i], parser->j + 1,
			ft_strlen(parser->tokens[parser->i]));
	parser->tokens[parser->i] = string_join(tmp, parser->tokens[parser->i]);
	parser->param_exp = 0;
	free (tmp2);
}

static void	expnad_var(t_parser *parser, t_env *env)
{
	char	*tmp;
	char	*tmp2;
	char	*var;
	int		i;

	tmp2 = parser->tokens[parser->i];
	tmp = ft_substr(parser->tokens[parser->i], 0, parser->j - 1);
	i = parser->j;
	while (parser->tokens[parser->i][i] && is_valid(parser->tokens[parser->i][i]))
		i++;
	var = ft_substr(parser->tokens[parser->i], parser->j, i - parser->j);
	if (ft_getenv(var, env))
	{
		parser->tokens[parser->i] = string_join(tmp,
				ft_strdup(ft_getenv(var, env)));
		parser->tokens[parser->i] = string_join(parser->tokens[parser->i],
				ft_substr(tmp2, i, ft_strlen(tmp2)));
	}
	else
		parser->tokens[parser->i] = string_join(tmp,
				ft_substr(tmp2, i, ft_strlen(tmp2)));
	parser->param_exp = 0;
	parser->j = get_index(parser->tokens[parser->i]);
	free (var);
	free (tmp2);
}

void	variables_expander(t_parser *parser, t_env *env)
{
	parser->i = -1;
	while (parser->tokens[++parser->i])
	{
		wildcards_expander(parser);
		parser->j = -1;
		parser->param_exp = 0;
		while (parser->tokens[parser->i][++parser->j])
		{
			if (parser->tokens[parser->i][parser->j] == '\'')
				break ;
			else if (parser->tokens[parser->i][parser->j] == '$')
				parser->param_exp = 1;
			else if (parser->param_exp
				&& (ft_isdigit(parser->tokens[parser->i][parser->j]
					&& parser->tokens[parser->i][parser->j] != '0'))
					&& parser->tokens[parser->i][parser->j - 1] == '$')
				truncate_digit(parser);
			else if (parser->param_exp
				&& (ft_isalpha(parser->tokens[parser->i][parser->j])
				|| ft_strchr("0_", parser->tokens[parser->i][parser->j])))
				expnad_var(parser, env);
		}
	}
}
