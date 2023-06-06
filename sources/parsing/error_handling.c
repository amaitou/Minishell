/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:54:45 by amait-ou          #+#    #+#             */
/*   Updated: 2023/06/06 19:49:25 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	assign_error_type(t_dlist *node, t_errors *error)
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
		else
			error->error_type = error_of_double_quotes;
	}
}

int	error_for_quotes(t_dlist *node)
{
	int		i;
	int		c;
	char	q;

	if (node->state == __s_quotes)
		q = '\'';
	else
		q = '\"';
	i = 0;
	c = 0;
	while (node->value[i])
	{
		if (node->value[i] == q)
			c++;
		++i;
	}
	return (c % 2 == 0);
}

void	check_errors(t_dlist *head, t_errors *error)
{
	t_dlist	*temp;

	temp = head;
	if (temp->type == __PIPE)
	{
		assign_error_type(temp, error);
		return ;
	}
	while (temp)
	{
		if ((temp->type != __WORD && temp->next && temp->next->type != __WORD)
			|| (temp->type != __WORD && !temp->next))
		{
			assign_error_type(temp, error);
			return ;
		}
		else
		{
			if (!error_for_quotes(temp))
			{
				assign_error_type(temp, error);
				return ;
			}
		}
		temp = temp->next;
	}
}

void	__error__(t_dlist	*head, t_errors *error)
{
	check_errors(head, error);
}

void	display_error(t_errors *error)
{
	if (error->error_type == error_of_pipeline)
		printf("bash: syntax error near unexpected token `|'\n");
	else if (error->error_type == error_of_redirection_heredoc)
		printf("bash: syntax error near unexpected token `<<'\n");
	else if (error->error_type == error_of_redirection_append)
		printf("bash: syntax error near unexpected token `>>'\n");
	else if (error->error_type == error_of_redirection_in)
		printf("bash: syntax error near unexpected token `<'\n");
	else if (error->error_type == error_of_redirection_out)
		printf("bash: syntax error near unexpected token `>'\n");
	else if (error->error_type == error_of_double_quotes)
		printf("bash: syntax error near unclosed double quotes\n");
	else if (error->error_type == error_of_single_quotes)
		printf("bash: syntax error neart unclosed single quotes\n");
	error->exit_staus = 2;
}
