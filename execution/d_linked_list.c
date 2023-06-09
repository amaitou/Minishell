/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_linked_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 21:01:11 by bbouagou          #+#    #+#             */
/*   Updated: 2023/06/09 22:59:06 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_dlist	*create_node(void)
{
	t_dlist	*new;

	new = (t_dlist *)malloc(sizeof(t_dlist));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_dlist	*last_node(t_dlist *head)
{
	t_dlist	*temp;

	temp = head;
	if (!temp)
		return (NULL);
	while (temp->next)
		temp = temp->next;
	return (temp);
}

void	append_node(t_dlist **head, t_dlist *new)
{
	t_dlist	*temp;

	temp = last_node(*head);
	if (temp)
	{
		temp->next = new;
		new->prev = temp;
		return ;
	}
	*head = new;
}

void	traverse_list(t_dlist *head)
{
	t_dlist	*temp;

	temp = head;
	if (!temp)
		return ;
	while (temp)
	{
		printf("\nvalue ---> %s\n", temp->cmd);
		printf("type  ---> %d\n", temp->type);
		printf("state  ---> %c\n", temp->type);
		temp = temp->next;
	}
}

void	free_nodes(t_dlist *head, int boolean)
{
	t_dlist	*temp;

	while (head)
	{
		temp = head;
		if (boolean)
		{
			if (temp->state == __S_QUOTES || temp->state == __D_QUOTES)
				free(temp->cmd);
		}
		free(temp);
		head = head->next;
	}
}
