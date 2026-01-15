/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoessedr <yoessedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 20:43:19 by yoessedr          #+#    #+#             */
/*   Updated: 2026/01/11 20:43:19 by yoessedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_array(char ***arr)
{
	int	index;

	index = -1;
	if (!arr)
		return ;
	if (!(*arr))
		return ;
	while ((*arr)[++index])
		free((*arr)[index]);
	free(*arr);
	(*arr) = NULL;
}
