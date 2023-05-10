/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:47:07 by amait-ou          #+#    #+#             */
/*   Updated: 2023/05/10 16:22:02 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	main(int ac, char **ag)
{
	char	*cmd;
	char	**tokens;

	(void)ac;
	(void)ag;
	while (1)
	{
		cmd = prompt_string();
		if (!cmd)
		{
			printf("None");
			cmd = prompt_string();
		}
		else
		{
			tokens = create_tokens(cmd);
			tokens_traversal(tokens);
		}
		add_history(cmd);
		free(cmd);
	}
	return (0);
}
