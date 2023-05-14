/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 14:56:20 by bbouagou          #+#    #+#             */
/*   Updated: 2023/05/14 17:24:00 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

static void	truncate_digit(t_lexer *l)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	tmp = (void *)0;
	while (l->tokens[l->i][i] != '$')
		i++;
	if (i)
		tmp = ft_substr(l->tokens[l->i], 0, i);
	tmp2 = l->tokens[l->i];
	l->tokens[l->i] = ft_substr(l->tokens[l->i], l->j + 1,
			ft_strlen(l->tokens[l->i]));
	l->tokens[l->i] = string_join(tmp, l->tokens[l->i]);
	l->param_exp = 0;
	free (tmp2);
}

static void	expnad_var(t_lexer *l)
{
	char	*tmp;
	char	*tmp2;
	char	*var;
	int		i;

	tmp2 = l->tokens[l->i];
	tmp = ft_substr(l->tokens[l->i], 0, l->j - 1);
	i = l->j;
	while (l->tokens[l->i][i] && l->tokens[l->i][i] != '$')
		i++;
	var = ft_substr(l->tokens[l->i], l->j, i - l->j);
	if (getenv(var))
	{
		l->tokens[l->i] = ft_strjoin(tmp, getenv(var));
		l->tokens[l->i] = string_join(l->tokens[l->i],
				ft_substr(tmp2, i, ft_strlen(tmp2)));
		free(tmp);
	}
	else
		l->tokens[l->i] = string_join(tmp,
				ft_substr(tmp2, i, ft_strlen(tmp2)));
	l->param_exp = 0;
	free (var);
	free (tmp2);
}

char	**expand_variables(t_lexer *l)
{
	l->i = -1;
	l->param_exp = 0;
	while (l->tokens[++l->i])
	{
		l->j = -1;
		while (l->tokens[l->i][++l->j])
		{
			if (l->tokens[l->i][l->j] == '$')
				l->param_exp = 1;
			else if (l->param_exp && ft_isdigit(l->tokens[l->i][l->j])
					&& l->tokens[l->i][l->j - 1] == '$')
				truncate_digit(l);
			else if (l->param_exp && ft_isalpha(l->tokens[l->i][l->j]))
				expnad_var(l);
		}
	}
	return (l->tokens);
}
