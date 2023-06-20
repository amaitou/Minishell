/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 11:02:01 by amait-ou          #+#    #+#             */
/*   Updated: 2023/06/20 16:50:56 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_dlist	*node_quotes(char *token, char quote)
{
	t_dlist	*node;

	node = create_node();
	if (quote == '\'')
		node->state = __s_quotes;
	else
		node->state = __d_quotes;
	node->value = ft_strdup(token);
	node->type = __WORD;
	free(token);
	return (node);
}

t_dlist	*node_redirection(char *token)
{
	t_dlist	*node;

	node = create_node();
	node->value = ft_strdup(token);
	node->state = __without_quotes;
	if (!ft_strcmp(node->value, ">"))
		node->type = __RED_OUT;
	else if (!ft_strcmp(node->value, ">>"))
		node->type = __RED_APP;
	else if (!ft_strcmp(node->value, "<"))
		node->type = __RED_IN;
	else if (!ft_strcmp(node->value, "<<"))
		node->type = __HEREDOC;
	free(token);
	return (node);
}

t_dlist	*node_pipeline(char *token)
{
	t_dlist	*node;

	node = create_node();
	node->value = ft_strdup(token);
	node->state = __without_quotes;
	node->type = __PIPE;
	free(token);
	return (node);
}

t_dlist	*node_word(char *token)
{
	t_dlist	*node;

	node = create_node();
	node->value = ft_strdup(token);
	node->state = __without_quotes;
	node->type = __WORD;
	free(token);
	return (node);
}
