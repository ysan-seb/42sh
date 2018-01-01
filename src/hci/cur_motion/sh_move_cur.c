/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_move_cur.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 20:52:19 by mdescamp          #+#    #+#             */
/*   Updated: 2017/12/02 20:52:22 by mdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

size_t	sh_move_cur(size_t pos, size_t dest, t_coord *coord, t_tc tc)
{
	int		vmove;
	int		hmove;

	tputs(tc.vi, 0, termput);
	vmove = coord[dest].y - coord[pos].y;
	hmove = vmove > 0 ? coord[dest].x : coord[dest].x - coord[pos].x;
	while (vmove)
	{
		tputs(vmove > 0 ? tc.dn : tc.up, 0, termput);
		vmove += vmove < 0 ? 1 : -1;
	}
	while (hmove)
	{
		tputs(hmove > 0 ? tc.nd : tc.le, 0, termput);
		hmove += hmove < 0 ? 1 : -1;
	}
	tputs(tc.ve, 0, termput);
	return (dest);
}
