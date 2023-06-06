/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 01:28:16 by amait-ou          #+#    #+#             */
/*   Updated: 2023/06/06 19:58:06 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_quotes(t_scanner *scanner)
{
	scanner->j = scanner->i++;
	while (scanner->command[scanner->i] != scanner->t_quote
		&& scanner->command[scanner->i])
		scanner->i++;
	if (scanner->command[scanner->i])
		scanner->line = string_join(scanner->line,
				ft_substr(scanner->command, scanner->j,
					scanner->i - scanner->j + 1));
	else
		scanner->line = string_join(scanner->line,
				ft_substr(scanner->command, scanner->j,
					scanner->i - scanner->j));
}

void	handle_operators(t_scanner *scanner)
{
	if (!ft_memcmp(scanner->command + scanner->i, ">>", 2)
		|| !ft_memcmp(scanner->command + scanner->i, "<<", 2))
	{
		scanner->line = string_join(scanner->line, ft_strdup("\n"));
		scanner->line = string_join(scanner->line,
				ft_substr(scanner->command, scanner->i, 2));
		scanner->line = string_join(scanner->line, ft_strdup("\n"));
		scanner->i++;
	}
	else
	{
		scanner->line = string_join(scanner->line, ft_strdup("\n"));
		scanner->line = string_join(scanner->line,
				ft_substr(scanner->command, scanner->i, 1));
		scanner->line = string_join(scanner->line, ft_strdup("\n"));
	}
}

void	command_splitter(t_scanner *scanner)
{
	while (scanner->command[scanner->i])
	{
		if (scanner->command[scanner->i] == '\"'
			|| scanner->command[scanner->i] == '\'')
		{
			scanner->t_quote = scanner->command[scanner->i];
			handle_quotes(scanner);
		}
		else if (ft_strchr("<>|", scanner->command[scanner->i]))
			handle_operators(scanner);
		else if (ft_strchr(" \t\n\v\f\r", scanner->command[scanner->i]))
			scanner->line = string_join(scanner->line, ft_strdup("\n"));
		else
			scanner->line = string_join(scanner->line,
					ft_substr(scanner->command, scanner->i, 1));
		scanner->i++;
	}
}

void	__scanner__(t_scanner *scanner)
{
	scanner->i = 0;
	scanner->line = NULL;
	command_splitter(scanner);
	scanner->tokens = ft_split(scanner->line, '\n');
	free(scanner->line);
}
