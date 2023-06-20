/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_leaks_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:01:33 by amait-ou          #+#    #+#             */
/*   Updated: 2023/06/20 16:48:10 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clear_lexer(t_dlist **lst, void (*del)(void *))
{
	t_dlist	*t;

	if (!del || !lst)
		return ;
	while ((*lst) != NULL)
	{
		t = *lst;
		del((*lst)->value);
		((*lst)) = (*lst)->next;
		free(t);
	}
	*lst = NULL;
}

void	clear_file(t_list **lst, void (*del)(void *))
{
	t_list	*t;

	if (!del || !lst)
		return ;
	while ((*lst) != NULL)
	{
		t = *lst;
		del((*lst)->name);
		free(t);
		((*lst)) = (*lst)->next;
	}
	*lst = NULL;
}

void	del(void	*string)
{
	free(string);
}

void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	if (tokens)
	{
		while (tokens[i])
		{
			if (tokens[i])
				free(tokens[i]);
			++i;
		}
		free(tokens);
	}
}

void	clear_parser(t_parser **lst, void (*del)(void *))
{
	t_parser	*t;

	if (!del || !lst)
		return ;
	while ((*lst) != NULL)
	{
		t = *lst;
		clear_file(&(*lst)->file, del);
		free_tokens(t->args);
		free(t);
		(*lst) = (*lst)->next;
	}
	*lst = NULL;
}
