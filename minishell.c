/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:47:07 by amait-ou          #+#    #+#             */
/*   Updated: 2023/05/07 11:16:44 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **ag)
{
	char	*cmd;

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
			printf("%s\n", cmd);
		free(cmd);
	}
	return (0);
}
