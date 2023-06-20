/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:50:58 by amait-ou          #+#    #+#             */
/*   Updated: 2023/06/20 16:51:12 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	display_lexer_helper(t_dlist *temp)
{
	if (temp->type == __RED_IN)
		printf("[.] type -> REDIRECTION_IN\n");
	else if (temp->type == __RED_OUT)
		printf("[.] type -> REDIRECTION_OUT\n");
	else if (temp->type == __RED_APP)
		printf("[.] type -> REDIRECTION_APPEND\n");
	else if (temp->type == __HEREDOC)
		printf("[.] type -> HEREDOC\n");
	else if (temp->type == __PIPE)
		printf("[.] type -> PIPE\n");
	else if (temp->type == __RED_OUT)
		printf("[.] type -> REDIRECTION_OUT");
	else if (temp->type == __RED_IN)
		printf("[.] type -> REDIRECTION_IN");
	else
		printf("[.] type -> WORD\n");
}

void	display_lexer(t_dlist *head)
{
	t_dlist	*temp;

	temp = head;
	while (temp)
	{
		printf("---------------------------------\n");
		printf("[.] value -> %s\n", temp->value);
		if (temp->state == __s_quotes)
			printf("[.] state -> IN_SINGLE_QUOTES\n");
		else if (temp->state == __d_quotes)
			printf("[.] state -> IN_DOUBLE_QUOTES\n");
		else
			printf("[.] state -> WITHOUT_QUOTES\n");
		display_lexer_helper(temp);
		printf("---------------------------------\n");
		temp = temp->next;
	}
}
