/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:52:29 by amait-ou          #+#    #+#             */
/*   Updated: 2023/05/14 00:07:43 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	main(void)
{
	char	*cmd;
	char	**tokens;

	while (1)
	{
		cmd = prompt_string();
		if (!cmd)
			printf("None");
		else
		{
			tokens = tokenizer(cmd);
			tokens_traversal(tokens);
			free_tokenizer(tokens);
			add_history(cmd);
			free(cmd);
		}
	}
	return (0);
}
