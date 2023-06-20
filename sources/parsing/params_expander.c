/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 12:15:04 by bbouagou          #+#    #+#             */
/*   Updated: 2023/06/20 15:45:00 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	truncate_digit(t_dlist *list)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	tmp = (void *)0;
	while (list->value[i] != '$')
		i++;
	if (i)
		tmp = ft_substr(list->value, 0, i);
	tmp2 = list->value;
	list->value = ft_substr(list->value,
			list->i + 1,
			ft_strlen(list->value));
	list->value = string_join(tmp, list->value);
	list->param_exp = 0;
	list->i -= 1;
	free(tmp2);
}

static void	expand_var(t_dlist *list, char *env[])
{
	char	*tmp;
	char	*tmp2;
	char	*var;
	int		i;

	tmp2 = list->value;
	tmp = ft_substr(list->value, 0, list->i - 1);
	i = list->i;
	while (list->value[i] && is_valid(list->value[i]))
		++i;
	var = ft_substr(list->value, list->i, i - list->i);
	if (ft_getenv(var, env))
	{
		list->value = string_join(tmp, ft_getenv(var, env));
		list->value = string_join(list->value,
				ft_substr(tmp2, i, ft_strlen(tmp2)));
	}
	else
		list->value = string_join(tmp,
				ft_substr(tmp2, i, ft_strlen(tmp2)));
	list->param_exp = 0;
	list->i -= 1;
	return (free(var), free(tmp2));
}

static void	expand_exit_status(t_dlist *list, int exit_status)
{
	char	*tmp;
	char	*tmp2;
	char	*var;
	int		i;

	tmp2 = list->value;
	tmp = ft_substr(list->value, 0, list->i - 1);
	i = list->i + 1;
	var = ft_substr(list->value, list->i, i - list->i);
	list->value = string_join(tmp, ft_itoa(exit_status));
	list->value = string_join(list->value,
			ft_substr(tmp2, i, ft_strlen(tmp2)));
	list->param_exp = 0;
	list->i -= 1;
	return (free(var), free(tmp2));
}

static void	check_character(t_dlist *list, char *env[])
{
	if (!list->param_exp)
		list->i = skip_quotes(list->value, list->i);
	if (list->value[list->i] == '$')
		list->param_exp = 1;
	else if (list->param_exp && ft_isdigit(list->value[list->i])
		&& list->value[list->i - 1] == '$')
		truncate_digit(list);
	else if (list->param_exp && list->value[list->i - 1] == '$'
		&& list->value[list->i] == '?')
		expand_exit_status(list, g_vars->exit_status);
	else if (list->param_exp && (is_valid(list->value[list->i])
			|| ft_strchr("\'\"", list->value[list->i])))
		expand_var(list, env);
	else
		list->param_exp = 0;
	list->i = skip_quotes(list->value, list->i);
	if (!list->value[list->i])
		list->i--;
}

void	params_expander(t_dlist *list, char *env[])
{
	while (list)
	{
		if (ft_strcmp(list->prev->value, "<<"))
		{
			wildcards_expander(list);
			list->i = -1;
			list->param_exp = 0;
			while (list->value[++list->i])
				check_character(list, env);
		}
		list = list->next;
	}
}
