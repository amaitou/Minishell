/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 12:15:04 by bbouagou          #+#    #+#             */
/*   Updated: 2023/06/14 13:13:16 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	truncate_digit(t_dlist **list)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	tmp = (void *)0;
	while ((*list)->value[i] != '$')
		i++;
	if (i)
		tmp = ft_substr((*list)->value, 0, i);
	tmp2 = (*list)->value;
	(*list)->value = ft_substr((*list)->value,
			(*list)->i + 1,
			ft_strlen((*list)->value));
	(*list)->value = string_join(tmp, (*list)->value);
	(*list)->param_exp = 0;
	free (tmp2);
}

static void	expnad_var(t_dlist **list, char *env[])
{
	char	*tmp;
	char	*tmp2;
	char	*var;
	int		i;

	tmp2 = (*list)->value;
	tmp = ft_substr((*list)->value, 0, (*list)->i - 1);
	i = (*list)->i;
	while ((*list)->value[i] && is_valid((*list)->value[i]))
		++i;
	var = ft_substr((*list)->value, (*list)->i, i - (*list)->i);
	if (ft_getenv(var, env))
	{
		(*list)->value = string_join(tmp, ft_strdup(ft_getenv(var, env)));
		(*list)->value = string_join((*list)->value,
				ft_substr(tmp2, i, ft_strlen(tmp2)));
	}
	else
		(*list)->value = string_join(tmp,
				ft_substr(tmp2, i, ft_strlen(tmp2)));
	(*list)->param_exp = 0;
	(*list)->i = get_index((*list)->value);
	return (free (var), free (tmp2));
}

t_dlist	*params_expander(t_dlist *list, char *env[])
{
	t_dlist *head;

	head = list;
	while (list)
	{
		if (ft_strcmp(list->prev->value, "<<"))
		{
			// wildcards_expander(list);
			list->i = skip_quotes(list->value);
			list->param_exp = 0;
			while (list->value[++list->i])
			{
				if (list->value[list->i] == '$')
					list->param_exp = 1;
				else if (list->param_exp
						&& (ft_isdigit(list->value
						&& list->value[list->i] != '0'))
						&& list->value[list->i - 1] == '$')
					truncate_digit(&list);
				else if (list->param_exp
					&& (ft_isalpha(list->value[list->i])
					|| ft_strchr("0_", list->value[list->i])))
					expnad_var(&list, env);
			}
		}
		list = list->next;
	}
	return (head);
}
