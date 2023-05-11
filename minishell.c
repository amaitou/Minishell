/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:47:07 by amait-ou          #+#    #+#             */
/*   Updated: 2023/05/11 03:03:24 by bbouagou         ###   ########.fr       */
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
			tokens = create_tokens(cmd);
			tokens_traversal(tokens);
			add_history(cmd);
			free(cmd);
		}
	}
	return (0);
}
