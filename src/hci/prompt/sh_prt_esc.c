/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_prt_esc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 15:46:59 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/11/16 15:47:00 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		sh_prt_esc(char buff[], int *b, char *ps)
{
	int		i;

	i = 1;
	if (*b == PRT_SIZE)
		*b = ft_flush_buff(buff, PRT_SIZE);
	buff[(*b)++] = 27;
	if (*b == PRT_SIZE)
		*b = ft_flush_buff(buff, PRT_SIZE);
	buff[*b] = ps[i++];
	if (buff[(*b)++] == '[')
	{
		while (ps[i] < '@' || ps[i] > '~')
		{
			if (*b == PRT_SIZE)
				*b = ft_flush_buff(buff, PRT_SIZE);
			buff[(*b)++] = ps[i++];
		}
		if (*b == PRT_SIZE)
			*b = ft_flush_buff(buff, PRT_SIZE);
		buff[(*b)++] = ps[i++];
	}
	return (i);
}
