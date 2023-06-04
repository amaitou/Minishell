/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_linked_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 00:25:43 by amait-ou          #+#    #+#             */
/*   Updated: 2023/06/04 01:00:06 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_dlist *create_node(void)
{
    t_dlist *new;

    new = (t_dlist *)malloc(sizeof(t_dlist));
    if (!new)
        return (NULL);
    new->next = NULL;
    new->prev = NULL;
    return (new);
}

t_dlist *last_node(t_dlist *head)
{
    t_dlist *temp;

    temp = head;
    if (!temp)
        return (NULL);
    while (temp->next)
        temp = temp->next;
    return (temp);
}

void    append_node(t_dlist **head, t_dlist *new)
{
    t_dlist *temp;

    temp = last_node(*head);
    if (temp)
    {
        temp->next = new;
        new->prev = temp;
        return;
    }
    *head = new;
}

void    traverse_list(t_dlist *head)
{
    t_dlist *temp;

    temp = head;
    if (!temp)
        return;
    while (temp)
    {
        printf("\nvalue ---> %s\n", temp->value);
        printf("type  ---> %d\n", temp->type);
        printf("state  ---> %c\n", temp->type);
        temp = temp->next;
    }
}