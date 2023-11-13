/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_expander_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:29:19 by bbouagou          #+#    #+#             */
/*   Updated: 2023/11/13 05:49:30 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	search(t_dlist *list, int i, int *j)
{
	if (!i && list->first && !ft_strnstr(list->p_match + *j,
			list->req[i], ft_strlen(list->req[i])))
	{
		*j = (size_t)(ft_strnstr(list->p_match + *j, list->req[i],
					ft_strlen(list->req[i])) - list->p_match);
		return (0);
	}
	else if (!list->req[i + 1] && list->last
		&& !ft_strlaststr(list->p_match + *j, list->req[i]))
	{
		*j = (size_t)(list->p_match - ft_strlaststr(list->p_match + *j,
					list->req[i]));
		return (0);
	}
	else if (!ft_strnstr(list->p_match + *j, list->req[i],
			ft_strlen(list->p_match)))
	{
		*j = (size_t)(list->p_match
				- ft_strnstr(list->p_match + *j, list->req[i],
					ft_strlen(list->p_match)));
		return (0);
	}
	return (1);
}

int	should_expand(char *string)
{
	int	i;

	i = 0;
	while (string[i] != '$' && string[i]
		&& !ft_strchr("'\"", string[i]))
		i++;
	return (ft_strlen(string) - i);
}

void	match_found(t_dlist *list)
{
	free(list->value);
	list->value = ft_strdup(list->matched);
	free (list->matched);
}

void	search_for_match(t_dlist *list)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	if (list->p_match[0] == '.')
	{
		free (list->p_match);
		return ;
	}
	while (list->req[++i])
		if (!search(list, i, &j))
			break ;
	if (!list->req[i])
	{
		list->matched = string_join(list->matched, list->p_match);
		list->matched = string_join(list->matched, ft_strdup(" "));
	}
	else
		free (list->p_match);
}
