/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:43:24 by amait-ou          #+#    #+#             */
/*   Updated: 2023/05/07 10:08:08 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*prompt_string(void)
{
	char	*cmd;

	cmd = readline("minishell $ ");
	return (cmd);
}
