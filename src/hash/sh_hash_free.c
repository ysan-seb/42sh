/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_hash_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 20:50:32 by mdescamp          #+#    #+#             */
/*   Updated: 2017/12/02 20:50:38 by mdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sh_hash_free(void)
{
	t_htable	**htable;
	t_htable	*ctable;
	t_htable	*tmp;
	int			*hindex;
	int			i;

	i = 0;
	htable = sh_htable();
	hindex = sh_hindex();
	while (hindex[i] >= 0)
	{
		ctable = htable[hindex[i]];
		while (ctable)
		{
			free(ctable->cmd);
			free(ctable->path);
			tmp = ctable->next;
			free(ctable);
			ctable = tmp;
		}
		i++;
	}
	sh_hash_init();
}
