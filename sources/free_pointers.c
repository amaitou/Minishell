/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pointers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:21:05 by amait-ou          #+#    #+#             */
/*   Updated: 2023/05/28 17:04:21 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../includes/minishell.h"

void	free_pointers(t_prompt *prompt, t_parser *parser)
{
	free(parser->cmd);
	free(parser);
	free(prompt->line);
	free(prompt);
}
