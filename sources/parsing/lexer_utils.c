/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:22:50 by amait-ou          #+#    #+#             */
/*   Updated: 2023/06/04 01:46:52 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_dlist *node_quotes(char *token, char quote)
{
	t_dlist	*node;

	node = create_node();
	if (quote == '\'')
		node->state = __s_quotes;
	else
		node->state = __d_quotes;
	node->value = token;
	node->type = __NONE;
	return (node);
}

t_dlist	*node_redirection(char *token)
{
	t_dlist	*node;
	
	node = create_node();
	node->value = token;
	node->state = __none;
	if (!ft_strcmp(token, ">"))
		node->type = __RED_OUT;
	else if (!ft_strcmp(token, ">>"))
		node->type = __RED_APP;
	else if (!ft_strcmp(token, "<"))
		node->type = __RED_IN;
	else if (!ft_strcmp(token, "<<"))
		node->type = __HEREDOC;
	return (node);
}

t_dlist	*node_pipeline(char *token)
{
	t_dlist *node;

	node = create_node();
	node->value = token;
	node->state = __none;
	node->type = __PIPE;
	return (node);
}

t_dlist *node_word(char *token)
{
	t_dlist *node;

	node = create_node();
	node->value = token;
	node->state = __none;
	node->type = __NONE;
	return (node);
}

void	lexer_traverse(t_dlist *head)
{
	t_dlist *temp;

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
		else
			printf("[.] type -> NO_TYPE\n");
		printf("---------------------------------\n");
		temp = temp->next;

	}
}