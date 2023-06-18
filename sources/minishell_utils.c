/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:29:11 by amait-ou          #+#    #+#             */
/*   Updated: 2023/06/18 10:26:27 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_spaces(char *s)
{
	while (*s && (*s == '\t' || *s == ' '))
		++s;
	if (*s)
		return (0);
	return (1);
}

void	free_pointers(t_prompt *prompt, t_scanner *scanner,
	t_errors *error)
{
	free(prompt->line);
	free(prompt);
	free(scanner->command);
	free_scanner(scanner->tokens);
	free(scanner);
	free(error);
}

int	__check__(t_scanner *scanner, t_prompt *prompt, t_errors *error)
{
	// (void)error;
	if (!scanner->command)
	{
		free(prompt);
		free(scanner);
		return (1);
	}
	if (check_spaces(scanner->command))
	{
		free(prompt->line);
		free(prompt);
		free(scanner->command);
		free(scanner);
		free(error);
		return (2);
	}
	return (0);
}

t_list	*mount_heredoc(t_list *files)
{
	t_list	*file;
	t_list	*heredoc;
	t_list	*traverser;

	file = files;
	heredoc = NULL;
	while (file)
	{
		if (file->type == HEREDOC)
		{
			ft_lstadd_back(&heredoc, ft_lstnew());
			traverser = ft_lstlast(heredoc);
			traverser->name = ft_strdup(file->name);
			traverser->type = HEREDOC;
		}
		file = file->next;
	}
	return (heredoc);
}

void	__parse__(t_scanner *scanner, t_dlist *head, t_errors *error,
	t_prompt *prompt, t_vars *vars)
{
	t_parser	*parser;

	parser = NULL;
	(void)prompt;
	__scanner__(scanner);
	__lexer__(&head, scanner);
	__error__(head, error);
	if (error->error_type != no_error)
	{
		display_error(error);
		free_nodes(head, 0);
	}
	else
	{
		head->prev = head;
		params_expander(head, vars->env);
		quotes_removal(head);
		__parser__(&parser, head);
		parser->prev = parser;
		executor(parser, vars);
		parser_traversal(parser);
	}
	add_history(scanner->command);
}
