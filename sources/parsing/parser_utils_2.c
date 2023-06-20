/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:52:44 by amait-ou          #+#    #+#             */
/*   Updated: 2023/06/20 16:53:54 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	display_for_files(t_parser *parser)
{
	printf("[.] FILES :\n");
	if (parser->file)
	{
		while (parser->file)
		{
			printf("\tName : %s\n", parser->file->name);
			if (parser->file->type == HEREDOC)
				printf("\tType : HEREDOC\n");
			else if (parser->file->type == APPEND)
				printf("\tType : RED_APPEND\n");
			else if (parser->file->type == IN)
				printf("\tType : RED_IN\n");
			else if (parser->file->type == OUT)
				printf("\tType : RED_OUT\n");
			parser->file = parser->file->next;
		}
	}
	else
		printf("\tNo Files\n");
}

void	display_parser(t_parser *parser)
{
	int	i;

	printf("----------------------\n");
	while (parser)
	{
		printf("[.] ARGS : \n\t");
		if (parser->args)
		{
			i = -1;
			while (parser->args[++i])
				printf("%s ", parser->args[i]);
		}
		else
			printf("No Args\n");
		printf("\n");
		display_for_files(parser);
		printf("[.] PIPE :\n");
		if (parser->type == __PIPE)
			printf("\tyes\n");
		else
			printf("\tNo\n");
		printf("----------------------\n");
		parser = parser->next;
	}
}
