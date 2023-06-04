/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:22:50 by amait-ou          #+#    #+#             */
/*   Updated: 2023/06/05 00:27:26 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_dlist *node_quotes(char *token, char quote)
{
	t_dlist	*node;
	char *temp;
	int	i;

	node = create_node();
	if (quote == '\'')
		node->state = __s_quotes;
	else
		node->state = __d_quotes;
	i = 0;
	temp = NULL;
	while (token[i])
	{
		if (!(token[i] == quote))
			temp = string_join(temp, ft_substr(token, i, 1));
		++i;
	}
	node->value = temp;
	node->type = __WORD;
	return (node);
}

t_dlist	*node_redirection(char *token)
{
	t_dlist	*node;
	
	node = create_node();
	node->value = token;
	node->state = __without_quotes;
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
	node->state = __without_quotes;
	node->type = __PIPE;
	return (node);
}

t_dlist *node_word(char *token)
{
	t_dlist *node;

	node = create_node();
	node->value = token;
	node->state = __without_quotes;
	node->type = __WORD;
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
			printf("[.] type -> WORD\n");
		printf("---------------------------------\n");
		temp = temp->next;

	}
}