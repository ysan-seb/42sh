/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_move_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 20:52:19 by mdescamp          #+#    #+#             */
/*   Updated: 2017/12/06 16:51:27 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

size_t	sh_move_line_u(t_line *line, t_coord *coord)
{
	int		pos;
	int		nl;

	nl = 0;
	if (coord[line->cur].y - 1 == 0)
	{
		pos = 0;
		while (line->str[pos] && coord[pos].y == 0)
			if (line->str[pos++] == '\n')
				nl = 1;
	}
	pos = coord[line->cur].x + (nl ? coord[0].x : 0);
	line->pos = line->cur;
	while (line->pos && (coord[line->pos].y > coord[line->cur].y - 1
				|| coord[line->pos].x > pos))
		line->pos -= 1;
	return (1);
}

size_t	sh_move_line_d(t_line *line, t_coord *coord)
{
	int		pos;
	int		nl;

	nl = 0;
	if (coord[line->cur].y == 0)
	{
		pos = 0;
		while (line->str[pos] && coord[pos].y == 0)
			if (line->str[pos++] == '\n')
				nl = 1;
	}
	pos = coord[line->cur].x - (nl ? coord[0].x : 0);
	line->pos = line->cur;
	while (line->str[line->pos] && (coord[line->pos].y < coord[line->cur].y + 1
				|| (coord[line->pos].x < pos
					&& coord[line->pos + 1].y == coord[line->cur].y + 1)))
		line->pos += 1;
	return (1);
}
