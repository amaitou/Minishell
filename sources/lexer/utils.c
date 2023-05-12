/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:34:01 by amait-ou          #+#    #+#             */
<<<<<<< HEAD:sources/lexer/utils.c
/*   Updated: 2023/05/12 17:52:57 by amait-ou         ###   ########.fr       */
=======
/*   Updated: 2023/05/11 00:09:23 by bbouagou         ###   ########.fr       */
>>>>>>> 41c761d0d448382e8165c2225a6c1b70b3ac6205:sources/lexer/lexer_utils.c
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

void	tokens_traversal(char **t)
{
	int	i;

	i = 0;
	while (t[i])
	{
		printf(" [.] %s\n", t[i]);
		++i;
	}
}
