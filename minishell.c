/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:52:29 by amait-ou          #+#    #+#             */
/*   Updated: 2023/05/12 20:52:32 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	main(int ac, char **ag, char **envp)
{
	char	*cmd;
	char	**tokens;

	(void)ac;
	(void)ag;
	(void)envp;
	while (1)
	{
		cmd = prompt_string();
		if (!cmd)
			printf("None");
		else
		{
			tokens = tokenizer(cmd);
			tokens_traversal(tokens);
			add_history(cmd);
			free(cmd);
		}
	}
	return (0);
}
