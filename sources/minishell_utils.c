/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:29:11 by amait-ou          #+#    #+#             */
/*   Updated: 2023/06/12 20:44:16 by amait-ou         ###   ########.fr       */
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

int	__check__(t_scanner *scanner, t_prompt *prompt)
{
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
		return (2);
	}
	return (0);
}

void	__parse__(t_scanner *scanner, t_dlist *head, t_errors *error,
	t_prompt *prompt)
{
	t_parser	*parser;

	parser = NULL;
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
		quotes_removal(head);
		__parser__(parser, head);
		free_nodes(head, 1);
	}
	add_history(scanner->command);
	free_pointers(prompt, scanner, error);
}
