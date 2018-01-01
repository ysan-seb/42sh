/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_edit_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 20:53:03 by mdescamp          #+#    #+#             */
/*   Updated: 2017/12/02 20:53:12 by mdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	sh_norme1_suite(t_line **line, t_tc *tc, char byte, int ret)
{
	if (((byte != 11 && byte != 21 && byte != 23 && byte != 25)))
		tc->cut = 0;
	if (byte == 18 || byte == 19)
		ret = sh_i_search(line, tc, byte == 18 ? 0 : 1);
	return (ret);
}

static int	sh_norme1(t_line **line, char *save, t_tc *tc)
{
	int		ret[2];
	char	byte;

	ft_memset(ret, 0, sizeof(int) * 2);
	byte = 0;
	if (read(0, &byte, 1) < 0 && g_signal != SIGWINCH)
		return (-1);
	else if (byte == 11 || byte == 21 || byte == 23 || byte == 25)
		ret[0] = sh_cvx(*line, &tc->coord, tc, byte);
	else if (byte == 27)
		ret[0] = sh_esc(line, &tc->coord, tc, ret + 1);
	else if (byte == 4)
		ret[0] = sh_ctrl_d(*line, save);
	else if (byte == '\n')
		ret[0] = sh_nl(*line, &tc->coord, *tc);
	else if (byte == '\t' && !save)
		ret[0] = sh_tab(*line, &tc->coord, *tc);
	else if (byte == 127)
		ret[0] = sh_del_l(*line, &tc->coord, *tc);
	else if (byte >= 32 && byte < 127)
		ret[0] = sh_ins(*line, byte);
	(*line)->h_smd = ret[1];
	ret[0] = sh_norme1_suite(line, tc, byte, ret[0]);
	return (ret[0]);
}

static int	sh_norme2(t_line *line, char *save, t_tc *tc, int success)
{
	if (g_signal == SIGWINCH)
	{
		free(tc->coord);
		if (!(tc->coord = sh_create_coord(line, tc->prompt)))
			return (-1);
	}
	if (success & DISP)
	{
		if (success & (DISP_FULL ^ DISP))
		{
			line->pos = line->cur;
			line->cur = 0;
			sh_prompt(save ? 2 : 1);
		}
		if (sh_display(line, &(tc->coord), *tc, save) < 0)
			return (-1);
	}
	return (0);
}

static int	sh_edit_free(t_coord *coord, int success)
{
	free(coord);
	if (g_signal == SIGINT)
		return (-1);
	return (success);
}

int			sh_edit_line(t_line **line, char *save, t_tc *tc)
{
	int		success;

	success = 0;
	if (!(tc->coord = sh_create_coord(*line, tc->prompt)))
		return (-1);
	while (g_signal != SIGINT && !(success & EOT) && !(success & EOL)
			&& !(success < 0))
	{
		success = sh_norme1(line, save, tc);
		if (g_signal == SIGINT)
			sh_move_cur((*line)->cur, (*line)->used, tc->coord, *tc);
		else if (sh_norme2(*line, save, tc, success) < 0)
			return (-1);
	}
	return (sh_edit_free(tc->coord, success));
}
