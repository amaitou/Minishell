/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traversing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:00:36 by amait-ou          #+#    #+#             */
/*   Updated: 2023/06/13 20:30:48 by amait-ou         ###   ########.fr       */
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

	while (head)
	{
		i = -1;
		printf("----------------------\n");
		printf("[.] ARGS : \n\t");
		while (head->args[++i])
			printf("%s ", head->args[i]);
		printf("\n");
		printf("[.] FILES :\n\t");
		i = -1;
		
		while (head->file[++i].name)
		{
			printf("Name : %s\n\t", head->file[i].name);
			if (head->file[i].type == __HEREDOC)
				printf("Type : HEREDOC\n\n\t");
			else if (head->file[i].type == __RED_APP)
				printf("Type : RED_APPEND\n\n\t");
			else if (head->file[i].type == __RED_IN)
				printf("Type : RED_IN\n\n\t");
			else if (head->file[i].type == __RED_OUT)
				printf("Type : RED_OUT\n\n\t");
		}
		printf("\n");
		printf("----------------------\n");
		head = head->next;
	}
}
