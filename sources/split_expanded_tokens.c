/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_expanded_tokens.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 02:52:50 by amait-ou          #+#    #+#             */
/*   Updated: 2023/06/24 03:03:15 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	assign_lexer_1(t_dlist *list, char **tmp)
{
	t_dlist	*tmp_n;
	int		i;

	tmp_n = NULL;
	i = 0;
	free(list->value);
	list->value = ft_strdup(tmp[i]);
	++i;
	while (list && tmp[i])
	{
		tmp_n = create_node();
		tmp_n->type = __WORD;
		tmp_n->value = ft_strdup(tmp[i]);
		tmp_n->prev = list;
		tmp_n->next = list->next;
		if (list->next)
			list->next->prev = tmp_n;
		list->next = tmp_n;
		list = list->next;
		++i;
	}
}

void	assign_lexer_2(t_dlist *list)
{
	if (!list->next)
	{
		free(list->value);
		list->value = ft_strdup("");
	}
	else
	{
		list->prev->next = list->next;
		free(list->value);
		free(list);
	}
}

void	split_expanded_tokens(t_dlist *list)
{
	char	**tmp;

	while (list)
	{
		if (!ft_strchr(list->value, '\'') && !ft_strchr(list->value, '\"')
			&& ft_strchr(list->value, ' '))
		{
			tmp = ft_split(list->value, ' ');
			if (tmp && tmp[0])
				assign_lexer_1(list, tmp);
			else
				assign_lexer_2(list);
			if (tmp)
				clean(tmp);
		}
		list = list->next;
	}
}
