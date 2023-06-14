/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traversing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:00:36 by amait-ou          #+#    #+#             */
/*   Updated: 2023/06/14 21:24:35 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	traverse_helper(t_dlist *head)
{
	t_dlist	*temp;

	temp = head;
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
}

void	lexer_traverse(t_dlist *head)
{
	t_dlist	*temp;

	temp = head;
	while (temp)
	{
		printf("---------------------------------\n");
		traverse_helper(temp);
		if (temp->type == __RED_APP)
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

void	scanner_traversal(char **scanner)
{
	int	i;

	i = -1;
	while (scanner[++i])
		printf(" [.] %s\n", scanner[i]);
}

void	parser_traversal(t_parser *head)
{
	int	i;

	printf("----------------------\n");
	while (head)
	{
		printf("[.] ARGS : \n\t");
		if (head->args)
		{
			i = -1;
			while (head->args[++i])
				printf("%s ", head->args[i]);
		}
		else
			printf("No Args\n");
		printf("\n");
		printf("[.] FILES :\n");
		if (head->file)
		{
			while (head->file)
			{
				printf("\tName : %s\n", head->file->name);
				if (head->file->type == HEREDOC)
					printf("\tType : HEREDOC\n");
				else if (head->file->type == APPEND)
					printf("\tType : RED_APPEND\n");
				else if (head->file->type == IN)
					printf("\tType : RED_IN\n");
				else if (head->file->type == OUT)
					printf("\tType : RED_OUT\n");
				head->file = head->file->next;
			}
		}
		else
			printf("\tNo Files\n");
		printf("[.] PIPE :\n");
		if (head->type == __PIPE)
			printf("\tyes\n");
		else
			printf("\tNo\n");
		printf("----------------------\n");
		head = head->next;
	}
}
