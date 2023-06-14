/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 15:07:23 by amait-ou          #+#    #+#             */
/*   Updated: 2023/06/13 23:19:44 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int	count_files(t_dlist	*head)
// {
// 	t_dlist	*temp;
// 	int		number;

// 	temp = head;
// 	number = 0;
// 	while (temp && temp->type != __PIPE)
// 	{
// 		if (temp->type == __RED_IN || temp->type == __RED_OUT
// 			|| temp->type == __RED_APP || temp->type == __HEREDOC)
// 			++number;
// 		temp = temp->next;
// 	}
// 	return (number);
// }

int	count_arguments(t_dlist *head)
{
	t_dlist	*temp;
	int		number;

	temp = head;
	number = 0;
	while (temp && temp->type != __PIPE)
	{
		if ((temp->type == __WORD && !temp->prev)
			|| (temp->type == __WORD && temp->prev->type == __WORD))
			++number;
		temp = temp->next;
	}
	return (number);
}

// void	assign_file(t_dlist *head, t_parser *node, int i)
// {
// 	node->file[i].type = head->type;
// 	node->file[i].name = ft_strdup(head->next->value);
// }

void	assign_args(t_dlist *head, t_parser *node, char *args)
{
	(void)head;
	node->args = ft_split(args, '\n');
}
