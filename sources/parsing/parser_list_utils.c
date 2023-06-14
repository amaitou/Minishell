/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:07:57 by amait-ou          #+#    #+#             */
/*   Updated: 2023/06/12 17:26:41 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_parser	*__create_node(void)
{
	t_parser	*new;

	new = (t_parser *)malloc(sizeof(t_parser));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_parser	*__last_node(t_parser *head)
{
	t_parser	*temp;

	temp = head;
	if (!temp)
		return (NULL);
	while (temp->next)
		temp = temp->next;
	return (temp);
}

void	__append_node(t_parser **head, t_parser *new)
{
	t_parser	*temp;

	temp = __last_node(*head);
	if (temp)
	{
		temp->next = new;
		new->prev = temp;
		return ;
	}
	*head = new;
}
