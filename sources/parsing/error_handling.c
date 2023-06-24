/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:17:21 by amait-ou          #+#    #+#             */
/*   Updated: 2023/06/24 01:58:45 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_types(t_dlist *node, t_errors *error)
{
	if (node->type == __PIPE)
		error->error_type = error_of_pipeline;
	else if (node->type == __RED_IN)
		error->error_type = error_of_redirection_in;
	else if (node->type == __RED_OUT)
		error->error_type = error_of_redirection_out;
	else if (node->type == __HEREDOC)
		error->error_type = error_of_redirection_heredoc;
	else if (node->type == __RED_APP)
		error->error_type = error_of_redirection_append;
	else
	{
		if (node->state == __s_quotes)
			error->error_type = error_of_single_quotes;
		else if (node->state == __d_quotes)
			error->error_type = error_of_double_quotes;
	}
}

int	check_quotes(t_dlist *temp)
{
	int		i;
	int		c;
	char	q;

	i = 0;
	c = 0;
	while (temp->value[i])
	{
		if (temp->value[i] == '\"' || temp->value[i] == '\'')
		{
			c = 1;
			q = temp->value[i];
			++i;
			while (temp->value[i] && temp->value[i] != q)
				++i;
		}
		if (temp->value[i] == q)
			c = 0;
		++i;
	}
	return (c == 0);
}

int	check_errors(t_dlist *temp, t_errors *error)
{
	if ((temp->type != __WORD && temp->next && temp->next->type != __WORD)
		|| (temp->type != __WORD && !temp->next))
	{
		error_types(temp, error);
		return (1);
	}
	if (!check_quotes(temp))
	{
		error_types(temp, error);
		return (2);
	}
	return (0);
}

void	__error__(t_minishell *minishell)
{
	t_dlist	*head;

	head = minishell->lexer;
	if (head->type == __PIPE)
	{
		error_types(head, minishell->error);
		return ;
	}
	while (head)
	{
		if (check_errors(head, minishell->error))
			return ;
		head = head->next;
	}
	minishell->error->error_type = no_error;
}

void	display_error(t_errors *error)
{
	if (error->error_type == error_of_space_redirection)
	{
		ft_putendl_fd(SPACE_REDIRECTION_ERROR, STDERR_FILENO);
		g_vars->exit_status = 1;
		return ;
	}
	if (error->error_type == error_of_ambiguous)
	{
		ft_putendl_fd(AMBIGUOUS_ERROR, STDERR_FILENO);
		g_vars->exit_status = 1;
		return ;
	}
	else
		display_error_helper(error);
}
