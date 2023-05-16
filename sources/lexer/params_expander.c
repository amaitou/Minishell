/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 14:56:20 by bbouagou          #+#    #+#             */
/*   Updated: 2023/05/16 18:12:12 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

static int	get_index(char *token)
{
	int	i;

	i = 0;
	while (token[i] && token[i] != '$')
		i++;
	return (--i);
}

static void	truncate_digit(t_lexer *lexer)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	tmp = (void *)0;
	while (lexer->tokens[lexer->i][i] != '$')
		i++;
	if (i)
		tmp = ft_substr(lexer->tokens[lexer->i], 0, i);
	tmp2 = lexer->tokens[lexer->i];
	lexer->tokens[lexer->i] = ft_substr(lexer->tokens[lexer->i], lexer->j + 1,
			ft_strlen(lexer->tokens[lexer->i]));
	lexer->tokens[lexer->i] = string_join(tmp, lexer->tokens[lexer->i]);
	lexer->param_exp = 0;
	free (tmp2);
}

static void	expnad_var(t_lexer *lexer)
{
	char	*tmp;
	char	*tmp2;
	char	*var;
	int		i;

	tmp2 = lexer->tokens[lexer->i];
	tmp = ft_substr(lexer->tokens[lexer->i], 0, lexer->j - 1);
	i = lexer->j;
	while (lexer->tokens[lexer->i][i] && (ft_isalpha(lexer->tokens[lexer->i][i])
		|| ft_isdigit(lexer->tokens[lexer->i][i]) || lexer->tokens[lexer->i][i] == '_'))
		i++;
	var = ft_substr(lexer->tokens[lexer->i], lexer->j, i - lexer->j);
	if (getenv(var))
	{
		lexer->tokens[lexer->i] = string_join(tmp, ft_strdup(getenv(var)));
		lexer->tokens[lexer->i] = string_join(lexer->tokens[lexer->i],
				ft_substr(tmp2, i, ft_strlen(tmp2)));
	}
	else
		lexer->tokens[lexer->i] = string_join(tmp,
				ft_substr(tmp2, i, ft_strlen(tmp2)));
	lexer->param_exp = 0;
	lexer->j = get_index(lexer->tokens[lexer->i]);
	free (var);
	free (tmp2);
}

void	variables_expander(t_lexer *lexer)
{
	lexer->i = -1;
	while (lexer->tokens[++lexer->i])
	{
		wildcards_expander(lexer);
		lexer->j = -1;
		lexer->param_exp = 0;
		while (lexer->tokens[lexer->i][++lexer->j])
		{
			if (lexer->tokens[lexer->i][lexer->j] == '\'')
				break ;
			else if (lexer->tokens[lexer->i][lexer->j] == '$')
				lexer->param_exp = 1;
			else if (lexer->param_exp && ft_isdigit(lexer->tokens[lexer->i][lexer->j])
					&& lexer->tokens[lexer->i][lexer->j - 1] == '$')
				truncate_digit(lexer);
			else if (lexer->param_exp && ft_isalpha(lexer->tokens[lexer->i][lexer->j]))
				expnad_var(lexer);
		}
	}
}
