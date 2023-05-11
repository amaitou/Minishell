/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:43:24 by amait-ou          #+#    #+#             */
/*   Updated: 2023/05/11 03:07:09 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

char	*prompt_string(void)
{
	return (readline("minishell $ "));
}
