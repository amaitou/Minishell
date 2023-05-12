/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:47:07 by amait-ou          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/05/12 20:47:00 by amait-ou         ###   ########.fr       */
=======
/*   Updated: 2023/05/11 03:03:24 by bbouagou         ###   ########.fr       */
>>>>>>> 41c761d0d448382e8165c2225a6c1b70b3ac6205
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
