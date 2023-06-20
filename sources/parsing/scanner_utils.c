/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:06:29 by amait-ou          #+#    #+#             */
/*   Updated: 2023/06/20 19:01:57 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	display_scanner(char **scanner)
{
	int	i;

	i = -1;
	while (scanner[++i])
		printf(" [.] %s\n", scanner[i]);
}
