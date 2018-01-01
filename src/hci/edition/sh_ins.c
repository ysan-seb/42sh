/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ins.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 20:52:54 by mdescamp          #+#    #+#             */
/*   Updated: 2017/12/02 20:53:12 by mdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		sh_ins(t_line *line, char c)
{
	if (line->used + 1 == line->capacity)
	{
		line->capacity += BUFF_SIZE;
		if (!(line->str = (char*)ft_realloc(line->str, line->used,
						line->capacity, sizeof(char))))
			return (-1);
	}
	ft_memmove(line->str + line->cur + 1, line->str + line->cur,
			ft_strlen(line->str + line->cur) + 1);
	line->str[line->cur] = c;
	line->used += 1;
	line->pos = line->cur + 1;
	return (LEXER | DISP);
}
