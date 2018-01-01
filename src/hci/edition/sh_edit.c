/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_edit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 11:01:31 by pguillie          #+#    #+#             */
/*   Updated: 2017/12/07 15:46:56 by mdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	edit_raz(t_line *line, t_tc *tc, t_token **lexer)
{
	g_signal = 0;
	ft_memset(line->str, 0, line->used);
	line->used = 0;
	line->cur = 0;
	line->h_smd = 0;
	line->h_pos = 0;
	tc->esc = NULL;
	sh_token_del(lexer);
}

static int	edit_save(char **save, char *line)
{
	char	*tmp;

	tmp = *save;
	*save = ft_strjoin(*save, line);
	free(tmp);
	if (!*save)
		return (-1);
	return (0);
}

static int	edit_end(t_token **lexer, int ret, char *save, char *last)
{
	if (!(ret < 0 || ret & EOT) && sh_hist_write(save, last))
		ft_error(SHELL, "Unable to write line in history", NULL);
	if (ret < 0 || ret & EOT || ret & SYN_ERR)
		sh_token_del(lexer);
	save ? ft_strdel(&save) : 0;
	return ((g_signal == SIGINT || ret == -42) ? 1 : ret);
}

static int	sh_lexing(int *ret, char **save, t_line *line, t_token **lexer)
{
	if (*ret < 0 || *ret == EOT || edit_save(save, line->str) < 0)
		return (1);
	if ((*ret = sh_lexer(lexer, save)) >= 0)
		line->used = ft_strlen(line->str);
	else if (*ret < 0)
		return (1);
	return (0);
}

int			sh_edit(t_line *line, char *last, t_token **lexer, t_tc *tc)
{
	struct termios	backup;
	char			*save;
	int				ret;

	if (term_raw(&backup, 0, 1))
		return (-1);
	ret = LEX_LOOP;
	save = NULL;
	while (ret & LEX_LOOP)
	{
		edit_raz(line, tc, lexer);
		tc->prompt = sh_prompt(!save ? 1 : 2);
		ret = sh_edit_line(&line, save, tc);
		ret = sh_hist_exp(line, ret);
		if (sh_lexing(&ret, &save, line, lexer))
			break ;
		ret = sh_verification(*lexer, ret);
	}
	if (tcsetattr(0, TCSANOW, &backup) < 0 && (ret = -1))
		ft_error(SHELL, "Unable to restore termios structure", NULL);
	return (edit_end(lexer, ret, save, last));
}
