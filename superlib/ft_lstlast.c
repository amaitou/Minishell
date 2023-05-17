/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 09:04:32 by amait-ou          #+#    #+#             */
/*   Updated: 2023/05/17 07:53:29 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./superlib.h"

t_env	*ft_lstlast(t_env *lst)
{
	if (!lst)
		return ((void *)0);
	while (lst->next != (void *)0)
		lst = lst->next;
	return (lst);
}
