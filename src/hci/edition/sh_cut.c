/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cut.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 20:53:08 by mdescamp          #+#    #+#             */
/*   Updated: 2017/12/06 15:50:41 by pbourlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	sh_move_word(t_line *line)
{
	int		pos;

	pos = line->cur - 1;
	while (line->str[pos] == ' ')
		pos -= 1;
	while (pos && line->str[pos] && line->str[pos] != ' ')
		pos -= 1;
	return (pos);
}

int			sh_cut_w(t_line *line, t_coord **coord, t_tc *tc)
{
	size_t	i;
	char	*cpy;

	i = 0;
	if (!line->str || line->cur == 0)
		return (0);
	i = sh_move_word(line);
	if (!tc->clipboard)
		cpy = ft_strnew(line->cur - i);
	else
		cpy = ft_strnew(line->cur - i + ft_strlen(tc->clipboard));
	ft_strncat(cpy, line->str + i, line->cur - i);
	tc->clipboard ? ft_strcat(cpy, tc->clipboard) : 0;
	ft_memmove(line->str + i, line->str + line->cur,
			ft_strlen(line->str + line->cur));
	ft_strclr(line->str + ft_strlen(line->str) - (line->cur - i));
	line->used -= line->cur - i;
	line->pos = i;
	line->cur = sh_move_cur(line->cur, line->pos, *coord, *tc);
	free(tc->clipboard);
	tc->clipboard = cpy;
	return (DISP | LEXER);
}

int			sh_cut_u(t_line *line, t_coord **coord, t_tc *tc)
{
	size_t	i;
	char	*cpy;

	i = line->cur;
	if (!line->str || line->cur == 0)
		return (0);
	if (!tc->clipboard)
		cpy = ft_strnew(line->cur + 1);
	else
		cpy = ft_strnew(ft_strlen(tc->clipboard) + line->cur);
	ft_strncat(cpy, line->str, i);
	tc->clipboard ? ft_strcat(cpy, tc->clipboard) : 0;
	ft_memmove(line->str, line->str + line->cur,
			ft_strlen(line->str + line->cur));
	ft_strclr(line->str + ft_strlen(line->str + line->cur));
	line->used -= line->cur;
	line->cur = sh_move_cur(line->cur, 0, *coord, *tc);
	line->pos = 0;
	free(tc->clipboard);
	tc->clipboard = cpy;
	return (DISP | LEXER);
}

int			sh_cut_k(t_line *line, t_tc *tc)
{
	size_t	i;
	size_t	j;
	char	*cpy;

	i = line->cur;
	j = ft_strlen(tc->clipboard);
	if (!line->str || line->cur == line->used)
		return (0);
	if (!tc->clipboard)
		cpy = ft_strnew(j + line->used - line->cur + 1);
	else
	{
		cpy = ft_strnew(ft_strlen(tc->clipboard) + line->used - line->cur);
		ft_strcat(cpy, tc->clipboard);
	}
	while (i < line->used)
	{
		cpy[j++] = line->str[i];
		line->str[i++] = '\0';
	}
	line->used -= (line->used - line->cur);
	free(tc->clipboard);
	tc->clipboard = cpy;
	return (DISP | LEXER);
}
